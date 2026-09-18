#ifndef RYUJINIII_KERNEL_HARDWARE_MONITOR_MOCK_H
#define RYUJINIII_KERNEL_HARDWARE_MONITOR_MOCK_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "led_line/kernel_hardware_monitor.h"

class KernelHardwareMonitorMock : public KernelHardwareMonitor {
public:
    ~KernelHardwareMonitorMock() override = default;
    std::string GetClassName() override { return "KernelHardwareMonitorMock"; }
    MOCK_METHOD(bool, IsHardwareNameAvailable, (), (override));
    MOCK_METHOD(std::string, TransformValue, (std::string value), (override));
    MOCK_METHOD(std::string, GetTitle, (), (override));
    MOCK_METHOD(std::string, GetInputValue, (), (override));
};

#endif // RYUJINIII_KERNEL_HARDWARE_MONITOR_MOCK_H
