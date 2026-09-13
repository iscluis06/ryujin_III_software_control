#ifndef RYUJINIII_AMD_CORE_LINE_MOCK_H
#define RYUJINIII_AMD_CORE_LINE_MOCK_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "led_line/amd_core_line.h"

class AmdCoreLineMock : public AmdCoreLine {
public:
    MOCK_METHOD(bool, IsHardwareNameAvailable, (), (override));
    MOCK_METHOD(std::string, GetHardwareMonitorNamePath, (), (override));
    MOCK_METHOD(std::string, GetInputValue, (), (override));
};


#endif // RYUJINIII_AMD_CORE_LINE_MOCK_H
