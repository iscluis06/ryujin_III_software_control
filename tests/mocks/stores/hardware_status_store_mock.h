#ifndef RYUJINIII_HARDWARE_STATUS_STORE_MOCK_H
#define RYUJINIII_HARDWARE_STATUS_STORE_MOCK_H
#include <gmock/gmock.h>
#include "stores/hardware_status_store.h"

class HardwareStatusStoreMock : public HardwareStatusStore {
public:
    MOCK_METHOD(const float, GetLiquidTemp, (), (const, override));
    MOCK_METHOD(const int, GetPumpSpeed, (), (const, override));
    MOCK_METHOD(const int, GetFanSpeed, (), (const, override));
    MOCK_METHOD(void, SetLiquidTemp, (float liquid_temp), (override));
    MOCK_METHOD(void, SetPumpSpeed, (int pump_speed), (override));
    MOCK_METHOD(void, SetFanSpeed, (int fan_speed), (override));
};

#endif // RYUJINIII_HARDWARE_STATUS_STORE_MOCK_H
