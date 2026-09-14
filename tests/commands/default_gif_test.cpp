#include "commands/default_gif_command.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class DefaultGifTest : public testing::Test {
protected:
    void SetUp() { this->wrapper_mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>(); }
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock;
};

TEST_F(DefaultGifTest, ExecuteSuccess) {
    DefaultGifCommand default_gif(this->wrapper_mock);
    ON_CALL(*(this->wrapper_mock.get()), SendInterrupt(testing::_, testing::_)).WillByDefault(testing::Return(true));
    EXPECT_CALL(*(this->wrapper_mock.get()), SendInterrupt).Times(2);
    EXPECT_EQ(default_gif.Execute(), true);
}

TEST_F(DefaultGifTest, ExecuteFail) {
    DefaultGifCommand default_gif(this->wrapper_mock);
    ON_CALL(*(this->wrapper_mock.get()), SendInterrupt(testing::_, testing::_)).WillByDefault(testing::Return(false));
    EXPECT_CALL(*(this->wrapper_mock.get()), SendInterrupt).Times(1);
    EXPECT_EQ(default_gif.Execute(), false);
}
