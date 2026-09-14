#include "ryujin_device.h"
#include <gtest/gtest.h>
#include "wrappers/libusb_wrapper.h"

class RyujinDeviceTest : public testing::Test {};

TEST_F(RyujinDeviceTest, ServiceTest) {
    std::shared_ptr<LibUsbWrapperBase> wrapper = std::make_shared<LibUsbWrapper>();
    RyujinDevice ryujin_device(wrapper);
    ryujin_device.Initialize();
    EXPECT_EQ(1, 1);
}
