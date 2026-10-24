#include "commands/hardware_monitor_chain_config.h"

#include <bits/this_thread_sleep.h>
#include <future>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class HardwareMonitorChainConfigTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::StrictMock<LibUsbWrapperMock>>();
        default_message = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::StrictMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_message;
};

std::shared_ptr<testing::StrictMock<LibUsbWrapperMock>> HardwareMonitorChainConfigTest::mock;
std::vector<unsigned char> HardwareMonitorChainConfigTest::default_message;

TEST_F(HardwareMonitorChainConfigTest, ConstructorLine1Success) {
    EXPECT_CALL(*(mock.get()), SendInterrupt(testing::_, testing::_))
            .Times(testing::AtLeast(8))
            .WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_message));
    HardwareMonitorChainConfig chain_config(mock);
    chain_config.AddLine(static_cast<int>(LedLineFactory::LedLineImplementations::AMD_CORE_TEMP));
    chain_config.SetMode(static_cast<int>(RyujinConstants::MonitorMode::PUNK));
    chain_config.SetStyle(static_cast<int>(RyujinConstants::MonitorStyle::STYLE01));
    auto chain_instance = chain_config.GetChain();
    std::future<bool> result = std::async(&HardwareMonitorChain::Execute, chain_instance.get());
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    HardwareMonitorChain::StopLoop(11);
    EXPECT_EQ(result.get(), true);
}

TEST_F(HardwareMonitorChainConfigTest, ConstructorLine2Success) {
    EXPECT_CALL(*(mock.get()), SendInterrupt(testing::_, testing::_))
            .Times(testing::AtLeast(9))
            .WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_message));
    HardwareMonitorChainConfig chain_config(mock);
    chain_config.AddLine(static_cast<int>(LedLineFactory::LedLineImplementations::AMD_CORE_TEMP));
    chain_config.AddLine(static_cast<int>(LedLineFactory::LedLineImplementations::RYUJIN_FAN_SPEED));
    chain_config.SetMode(static_cast<int>(RyujinConstants::MonitorMode::PUNK));
    chain_config.SetStyle(static_cast<int>(RyujinConstants::MonitorStyle::STYLE01));
    auto chain_instance = chain_config.GetChain();
    std::future<bool> result = std::async(&HardwareMonitorChain::Execute, chain_instance.get());
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    HardwareMonitorChain::StopLoop(11);
    EXPECT_EQ(result.get(), true);
}

TEST_F(HardwareMonitorChainConfigTest, ConstructorLine3Success) {
    EXPECT_CALL(*(mock.get()), SendInterrupt(testing::_, testing::_))
            .Times(testing::AtLeast(10))
            .WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(mock.get()), FillArray).WillRepeatedly(testing::Return(default_message));
    HardwareMonitorChainConfig chain_config(mock);
    chain_config.AddLine(static_cast<int>(LedLineFactory::LedLineImplementations::AMD_CORE_TEMP));
    chain_config.AddLine(static_cast<int>(LedLineFactory::LedLineImplementations::RYUJIN_FAN_SPEED));
    chain_config.SetMode(static_cast<int>(RyujinConstants::MonitorMode::PUNK));
    chain_config.SetStyle(static_cast<int>(RyujinConstants::MonitorStyle::STYLE01));
    auto chain_instance = chain_config.GetChain();
    std::future<bool> result = std::async(&HardwareMonitorChain::Execute, chain_instance.get());
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    HardwareMonitorChain::StopLoop(11);
    EXPECT_EQ(result.get(), true);
}
