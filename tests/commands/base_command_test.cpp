#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "commands/base_command_mock.h"
#include "libusb_wrapper_mock.h"

class BaseCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        first_message = {74, 65, 73, 74};
        second_message = {74, 65, 73, 73};
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> first_message;
    static std::vector<unsigned char> second_message;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> BaseCommandTest::mock;
std::vector<unsigned char> BaseCommandTest::first_message;
std::vector<unsigned char> BaseCommandTest::second_message;

TEST_F(BaseCommandTest, IsMessageValidSuccess) {
    BaseCommandMock base_command(mock);
    EXPECT_EQ(base_command.IsMessageValid(this->first_message), true);
}

TEST_F(BaseCommandTest, IsMessageValidFail) {
    testing::NiceMock<BaseCommandMock> base_command(mock);
    base_command.SetValidationMessage(first_message);
    EXPECT_EQ(base_command.IsMessageValid(second_message), false);
}
