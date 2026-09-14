#include "commands/turn_on_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class TurnOnCommandTest : public testing::Test {
protected:
    void SetUp() { mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>(); }
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    std::vector<unsigned char> default_array = std::vector<unsigned char>(65, 0);
};

TEST_F(TurnOnCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    TurnOnCommand turn_on_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));
    EXPECT_EQ(turn_on_command.Execute(), true);
}

TEST_F(TurnOnCommandTest, ExecuteFail) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    TurnOnCommand turn_on_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(turn_on_command.Execute(), false);
}
