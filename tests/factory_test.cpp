#include "factory.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "build_args_parser.h"
#include "commands/default_gif_command.h"
#include "commands/select_gif_command.h"
#include "commands/turn_off_command.h"
#include "commands/turn_on_command.h"
#include "mocks/libusb_wrapper_mock.h"

class FactoryTest : public testing::Test {
protected:
    BuildArgsParser *build_args = nullptr;
    void BuildArgs() {
        if (build_args == nullptr) {
            build_args = new BuildArgsParser();
        }
    }
    void SetUp() {
        this->BuildArgs();
        this->mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        this->factory = std::make_shared<Factory>(this->mock);
    }

    void CommandTest(std::vector<std::string> args, std::unique_ptr<BaseCommand> command_expected, bool equal) {
        this->build_args->GetParser()->ParseArgs(args);
        auto command = this->factory->GetCommand(*this->build_args->GetParser());
        bool are_names_equal = command->GetClassName() == command_expected->GetClassName();
        EXPECT_EQ(equal, are_names_equal);
    }
    std::shared_ptr<Factory> factory;
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    std::vector<unsigned char> default_array = std::vector<unsigned char>(65, 0);
};

TEST_F(FactoryTest, DefaultGifCommandSuccess) {
    CommandTest(std::vector<std::string>{"--default-gif"}, std::make_unique<DefaultGifCommand>(this->mock), true);
}
TEST_F(FactoryTest, DefaultGifCommandFail) {
    CommandTest(std::vector<std::string>{"--default-gif"}, std::make_unique<TurnOnCommand>(this->mock), false);
}
TEST_F(FactoryTest, TurnOnCommandSuccess) {
    CommandTest(std::vector<std::string>{"--lon"}, std::make_unique<TurnOnCommand>(this->mock), true);
}
TEST_F(FactoryTest, TurnOnCommandFail) {
    CommandTest(std::vector<std::string>{"--lon"}, std::make_unique<DefaultGifCommand>(this->mock), false);
}
TEST_F(FactoryTest, TurnOffCommandSuccess) {
    CommandTest(std::vector<std::string>{"--loff"}, std::make_unique<TurnOffCommand>(this->mock), true);
}
TEST_F(FactoryTest, TurnOffCommandFail) {
    CommandTest(std::vector<std::string>{"--loff"}, std::make_unique<DefaultGifCommand>(this->mock), false);
}
TEST_F(FactoryTest, SelectGifCommandSuccess) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillRepeatedly(testing::Return(this->default_array));
    CommandTest(std::vector<std::string>{"--select-gif", "1"}, std::make_unique<SelectGifCommand>(this->mock, 1), true);
}
TEST_F(FactoryTest, SelectGifCommandFail) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillRepeatedly(testing::Return(this->default_array));
    CommandTest(std::vector<std::string>{"--select-gif", "1"}, std::make_unique<DefaultGifCommand>(this->mock), false);
}
TEST_F(FactoryTest, InvalidCommand) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillRepeatedly(testing::Return(this->default_array));
    EXPECT_THROW(this->build_args->GetParser()->ParseArgs(std::vector<std::string>{"invalid-command"}),
                 args::ParseError);
    auto command = this->factory->GetCommand(*this->build_args->GetParser());
    EXPECT_EQ(command, nullptr);
}
