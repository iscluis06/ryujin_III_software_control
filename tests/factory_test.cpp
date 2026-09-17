#include "factory.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "build_args_parser.h"
#include "commands/default_gif_command.h"
#include "commands/hardware_monitor_chain.h"
#include "commands/select_gif_command.h"
#include "commands/turn_off_command.h"
#include "commands/turn_on_command.h"
#include "commands/upload_chain.h"
#include "file_handle.h"
#include "magick_tool.h"
#include "mocks/libusb_wrapper_mock.h"

class FactoryTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        build_args = std::make_shared<BuildArgsParser>();
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        factory = std::make_shared<Factory>(mock);
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() {
        build_args.reset();
        mock.reset();
        factory.reset();
    }

    static void CommandTest(const std::vector<std::string> &args, const std::unique_ptr<ExecuteBase> &command_expected,
                            bool equal) {
        build_args->GetParser()->ParseArgs(args);
        auto command = factory->GetCommand(*build_args->GetParser());
        bool are_names_equal = command->GetClassName() == command_expected->GetClassName();
        EXPECT_EQ(equal, are_names_equal);
    }
    static std::shared_ptr<Factory> factory;
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
    static std::shared_ptr<BuildArgsParser> build_args;
};

std::shared_ptr<Factory> FactoryTest::factory;
std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> FactoryTest::mock;
std::vector<unsigned char> FactoryTest::default_array;
std::shared_ptr<BuildArgsParser> FactoryTest::build_args;

TEST_F(FactoryTest, DefaultGifCommandSuccess) {
    CommandTest(std::vector<std::string>{"--default-gif"}, std::make_unique<DefaultGifCommand>(mock), true);
}
TEST_F(FactoryTest, DefaultGifCommandFail) {
    CommandTest(std::vector<std::string>{"--default-gif"}, std::make_unique<TurnOnCommand>(mock), false);
}
TEST_F(FactoryTest, TurnOnCommandSuccess) {
    CommandTest(std::vector<std::string>{"--lon"}, std::make_unique<TurnOnCommand>(mock), true);
}
TEST_F(FactoryTest, TurnOnCommandFail) {
    CommandTest(std::vector<std::string>{"--lon"}, std::make_unique<DefaultGifCommand>(mock), false);
}
TEST_F(FactoryTest, TurnOffCommandSuccess) {
    CommandTest(std::vector<std::string>{"--loff"}, std::make_unique<TurnOffCommand>(mock), true);
}
TEST_F(FactoryTest, TurnOffCommandFail) {
    CommandTest(std::vector<std::string>{"--loff"}, std::make_unique<DefaultGifCommand>(mock), false);
}
TEST_F(FactoryTest, SelectGifCommandSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    CommandTest(std::vector<std::string>{"--select-gif", "1"}, std::make_unique<SelectGifCommand>(mock, 1), true);
}
TEST_F(FactoryTest, SelectGifCommandFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    CommandTest(std::vector<std::string>{"--select-gif", "1"}, std::make_unique<DefaultGifCommand>(mock), false);
}
TEST_F(FactoryTest, DefaultHardwareMonitorSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    CommandTest(std::vector<std::string>{"--hw-monitor"}, std::make_unique<HardwareMonitorChain>(mock), true);
}
TEST_F(FactoryTest, DefaultHardwareMonitorConfigSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    CommandTest(std::vector<std::string>{"--hw-monitor-config", "--line1", "1", "--mode", "1", "--style", "1"},
                std::make_unique<HardwareMonitorChain>(mock), true);
}
TEST_F(FactoryTest, UploadGifSuccess) {
    std::shared_ptr<FileHandleBase> file_handle = std::make_shared<FileHandle>();
    std::shared_ptr<TransformToolBase> transform_tool = std::make_shared<MagickTool>();
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    CommandTest(std::vector<std::string>{"--upload-gif", "test", "--select-gif", "1"},
                std::make_unique<UploadChain>(transform_tool, file_handle, mock, "test", 1), true);
}

TEST_F(FactoryTest, InvalidCommand) {
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    EXPECT_THROW(build_args->GetParser()->ParseArgs(std::vector<std::string>{"invalid-command"}), args::ParseError);
    auto command = factory->GetCommand(*build_args->GetParser());
    EXPECT_EQ(command, nullptr);
}
