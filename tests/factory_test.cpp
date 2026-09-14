#include "factory.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "commands/default_gif_command.h"
#include "commands/select_gif_command.h"
#include "commands/turn_off_command.h"
#include "commands/turn_on_command.h"
#include "mocks/libusb_wrapper_mock.h"

class FactoryTest : public testing::Test {
protected:
    void SetUp() {
        this->mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        this->factory = std::make_shared<Factory>(this->mock);
    }
    void CommandTest(const std::string &command_name, std::unique_ptr<BaseCommand> command_expected, bool equal) {
        auto command = this->factory->GetCommand(command_name);
        bool are_names_equal = command->GetClassName() == command_expected->GetClassName();
        EXPECT_EQ(equal, are_names_equal);
    }
    void CommandTest(const std::string &command_name, std::unique_ptr<BaseCommand> command_expected, int index,
                     bool equal) {
        auto command = this->factory->GetCommand(command_name, index);
        bool are_names_equal = command->GetClassName() == command_expected->GetClassName();
        EXPECT_EQ(equal, are_names_equal);
    }
    std::shared_ptr<Factory> factory;
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    std::vector<unsigned char> default_array = std::vector<unsigned char>(65, 0);
};

TEST_F(FactoryTest, DefaultGifCommandSuccess) {
    CommandTest("default_gif", std::make_unique<DefaultGifCommand>(this->mock), true);
}
TEST_F(FactoryTest, DefaultGifCommandFail) {
    CommandTest("default_gif", std::make_unique<TurnOnCommand>(this->mock), false);
}
TEST_F(FactoryTest, TurnOnCommandSuccess) { CommandTest("turn_on", std::make_unique<TurnOnCommand>(this->mock), true); }
TEST_F(FactoryTest, TurnOnCommandFail) {
    CommandTest("turn_on", std::make_unique<DefaultGifCommand>(this->mock), false);
}
TEST_F(FactoryTest, TurnOffCommandSuccess) {
    CommandTest("turn_off", std::make_unique<TurnOffCommand>(this->mock), true);
}
TEST_F(FactoryTest, TurnOffCommandFail) {
    CommandTest("turn_off", std::make_unique<DefaultGifCommand>(this->mock), false);
}
TEST_F(FactoryTest, SelectGifCommandSuccess) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillRepeatedly(testing::Return(this->default_array));
    CommandTest("select_gif_from_memory", std::make_unique<SelectGifCommand>(this->mock, 1), 1, true);
}
TEST_F(FactoryTest, SelectGifCommandFail) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillRepeatedly(testing::Return(this->default_array));
    CommandTest("select_gif_from_memory", std::make_unique<DefaultGifCommand>(this->mock), 1, false);
}
TEST_F(FactoryTest, InvalidCommand) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillRepeatedly(testing::Return(this->default_array));
    auto command = this->factory->GetCommand("invalid_command");
    EXPECT_EQ(command, nullptr);
}
