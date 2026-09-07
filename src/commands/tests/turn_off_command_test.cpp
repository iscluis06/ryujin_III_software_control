#include "commands/turn_off_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class TurnOffCommandTest : public testing::Test {};

TEST_F(TurnOffCommandTest, ExecuteSuccess) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    TurnOffCommand turn_off_command(wrapper_mock);
    std::vector<unsigned char> default_array(65, 0);
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillOnce(testing::Return(true));
    EXPECT_EQ(turn_off_command.Execute(), true);
}

TEST_F(TurnOffCommandTest, ExecuteFail) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    std::vector<unsigned char> size = {0x00, 0xff, 0x1f};
    TurnOffCommand turn_off_command(wrapper_mock);
    std::vector<unsigned char> default_array(65, 0);
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(turn_off_command.Execute(), false);
}
