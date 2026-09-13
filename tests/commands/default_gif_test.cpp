#include "commands/default_gif_command.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class DefaultGifTest : public testing::Test {};

TEST_F(DefaultGifTest, ExecuteSuccess) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    DefaultGifCommand default_gif(mock);
    ON_CALL(*(mock.get()), SendInterrupt(testing::_, testing::_)).WillByDefault(testing::Return(true));
    EXPECT_CALL(*(mock.get()), FillArray).Times(1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).Times(2);
    EXPECT_EQ(default_gif.Execute(), true);
}

TEST_F(DefaultGifTest, ExecuteFail) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    DefaultGifCommand default_gif(mock);
    ON_CALL(*(mock.get()), SendInterrupt(testing::_, testing::_)).WillByDefault(testing::Return(false));
    EXPECT_CALL(*(mock.get()), FillArray).Times(1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).Times(2);
    EXPECT_EQ(default_gif.Execute(), false);
}
