#include "ryujin_device.h"
#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class RyujinDeviceTest : public testing::Test {};

TEST_F(RyujinDeviceTest, ServiceTest) {
    std::shared_ptr<LibUsbWrapperMock> wrapper = std::make_shared<LibUsbWrapperMock>();
    EXPECT_CALL(*(wrapper.get()), ReleaseInterface).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*(wrapper.get()), InitializeDevice).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*(wrapper.get()), ClaimInterfaces).WillRepeatedly(::testing::Return(true));
    RyujinDevice ryujin_device(wrapper);
    EXPECT_EQ(ryujin_device.Initialize(), true);
}
