#include "commands/start_instruction_command.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class StartInstructionCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> StartInstructionCommandTest::mock;
std::vector<unsigned char> StartInstructionCommandTest::default_array;

TEST_F(StartInstructionCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    StartInstructionCommand start_instruction_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_EQ(start_instruction_command.Execute(), true);
}

TEST_F(StartInstructionCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    StartInstructionCommand start_instruction_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(start_instruction_command.Execute(), false);
}
