#include "commands/hardware_monitor_chain.h"


#include <future>
#include <gtest/gtest.h>
#include <thread>

#include "libusb_wrapper_mock.h"

class HardwareMonitorChainTest : public testing::Test {
protected:
    static std::shared_ptr<LibUsbWrapperMock> mock;
    static std::vector<unsigned char> default_array;
    static void SetUpTestSuite() {
        mock = std::make_shared<LibUsbWrapperMock>();
        default_array = std::vector<unsigned char>(65, 0);
    };
    static void TearDownTestSuite() { mock.reset(); };
};

std::shared_ptr<LibUsbWrapperMock> HardwareMonitorChainTest::mock;
std::vector<unsigned char> HardwareMonitorChainTest::default_array;

TEST_F(HardwareMonitorChainTest, ExecuteSuccess) {
    EXPECT_CALL((*mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_CALL((*mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    HardwareMonitorChain chain_test(mock);
    std::future<bool> result = std::async(&HardwareMonitorChain::Execute, &chain_test);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    HardwareMonitorChain::StopLoop(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_EQ(result.get(), true);
}

TEST_F(HardwareMonitorChainTest, ExecuteFail) {
    EXPECT_CALL((*mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_CALL((*mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    HardwareMonitorChain chain_test(mock);
    std::future<bool> result = std::async(&HardwareMonitorChain::Execute, &chain_test);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    HardwareMonitorChain::StopLoop(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_EQ(result.get(), false);
}
