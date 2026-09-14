#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "commands/base_command_mock.h"
#include "libusb_wrapper_mock.h"

class BaseCommandTest : public testing::Test {
protected:
    void SetUp() { this->mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>(); }
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    std::vector<unsigned char> first_message = {74, 65, 73, 74};
    std::vector<unsigned char> second_message = {74, 65, 73, 73};
};

TEST_F(BaseCommandTest, IsMessageValidSuccess) {
    BaseCommandMock base_command(this->mock);
    EXPECT_EQ(base_command.IsMessageValid(this->first_message), true);
}

TEST_F(BaseCommandTest, IsMessageValidFail) {
    BaseCommandMock base_command(this->mock);
    base_command.SetValidationMessage(this->first_message);
    EXPECT_EQ(base_command.IsMessageValid(this->second_message), false);
}
