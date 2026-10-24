#include "commands/hardware_monitor_style_command.h"
#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class HardwareMonitorStyleCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        wrapper = std::make_shared<LibUsbWrapperMock>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { wrapper.reset(); }
    static std::shared_ptr<LibUsbWrapperMock> wrapper;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<LibUsbWrapperMock> HardwareMonitorStyleCommandTest::wrapper;
std::vector<unsigned char> HardwareMonitorStyleCommandTest::default_array;

TEST_F(HardwareMonitorStyleCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(wrapper.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    EXPECT_CALL(*(wrapper.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    HardwareMonitorStyleCommand hardware_monitor_style_command(wrapper, 0, 0, 0);
    EXPECT_EQ(hardware_monitor_style_command.Execute(), true);
}

TEST_F(HardwareMonitorStyleCommandTest, ExecuteFail) {
    EXPECT_CALL(*(wrapper.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    EXPECT_CALL(*(wrapper.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    HardwareMonitorStyleCommand hardware_monitor_style_command(wrapper, 0, 0, 0);
    EXPECT_EQ(hardware_monitor_style_command.Execute(), false);
}
