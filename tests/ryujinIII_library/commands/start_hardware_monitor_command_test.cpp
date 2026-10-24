#include "commands/start_hardware_monitor_command.h"
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class StartHardwareMonitorCommandTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        wrapper_mock = std::make_shared<LibUsbWrapperMock>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { wrapper_mock.reset(); }
    static std::shared_ptr<LibUsbWrapperMock> wrapper_mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<LibUsbWrapperMock> StartHardwareMonitorCommandTest::wrapper_mock;
std::vector<unsigned char> StartHardwareMonitorCommandTest::default_array;

TEST_F(StartHardwareMonitorCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    StartHardwareMonitorCommand start_hardware_monitor_command(wrapper_mock);
    EXPECT_EQ(start_hardware_monitor_command.Execute(), true);
}

TEST_F(StartHardwareMonitorCommandTest, ExecuteFail) {
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    StartHardwareMonitorCommand start_hardware_monitor_command(wrapper_mock);
    EXPECT_EQ(start_hardware_monitor_command.Execute(), false);
}
