#include <gtest/gtest.h>
#include "led_line/kernel_hardware_monitor_mock.h"

class KernelHardwareMonitorTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        default_title = "KHM Mock";
        default_value = "Value Mock";
    }
    static std::string default_title;
    static std::string default_value;
};

std::string KernelHardwareMonitorTest::default_title;
std::string KernelHardwareMonitorTest::default_value;

TEST_F(KernelHardwareMonitorTest, GetTitleSuccess) {
    KernelHardwareMonitorMock hardware_monitor_mock;
    EXPECT_CALL(hardware_monitor_mock, GetTitle).WillRepeatedly(testing::Return(default_title));
    EXPECT_EQ(hardware_monitor_mock.GetTitle(), default_title);
}

TEST_F(KernelHardwareMonitorTest, GetTitleFail) {
    KernelHardwareMonitorMock hardware_monitor_mock;
    EXPECT_CALL(hardware_monitor_mock, GetTitle).WillRepeatedly(testing::Return(default_title));
    EXPECT_NE(hardware_monitor_mock.GetTitle(), "");
}

TEST_F(KernelHardwareMonitorTest, GetLineSuccess) {
    KernelHardwareMonitorMock hardware_monitor_mock;
    EXPECT_CALL(hardware_monitor_mock, IsHardwareNameAvailable).Times(1).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(hardware_monitor_mock, GetInputValue).Times(1).WillRepeatedly([]() { return default_value; });
    EXPECT_CALL(hardware_monitor_mock, TransformValue).Times(1).WillRepeatedly([](const std::string &value) {
        return default_value;
    });
    EXPECT_EQ(hardware_monitor_mock.GetLine(), default_value);
}

TEST_F(KernelHardwareMonitorTest, GetLineFailHardwareAvailable) {
    KernelHardwareMonitorMock hardware_monitor_mock;
    EXPECT_CALL(hardware_monitor_mock, IsHardwareNameAvailable).Times(1).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(hardware_monitor_mock, GetInputValue).Times(0);
    EXPECT_CALL(hardware_monitor_mock, TransformValue).Times(0);
    EXPECT_EQ(hardware_monitor_mock.GetLine(), "");
}
