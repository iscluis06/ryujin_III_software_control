#include "commands/default_gif_command.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class DefaultGifTest : public testing::Test {
protected:
    static void SetUpTestSuite() { wrapper_mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>(); }
    static void TearDownTestSuite() { wrapper_mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> DefaultGifTest::wrapper_mock;

TEST_F(DefaultGifTest, ExecuteSuccess) {
    DefaultGifCommand default_gif(wrapper_mock);
    ON_CALL(*(wrapper_mock.get()), SendInterrupt(testing::_, testing::_)).WillByDefault(testing::Return(true));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).Times(2);
    EXPECT_EQ(default_gif.Execute(), true);
}

TEST_F(DefaultGifTest, ExecuteFail) {
    DefaultGifCommand default_gif(wrapper_mock);
    ON_CALL(*(wrapper_mock.get()), SendInterrupt(testing::_, testing::_)).WillByDefault(testing::Return(false));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).Times(1);
    EXPECT_EQ(default_gif.Execute(), false);
}
