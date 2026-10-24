#include "stores/hardware_status_store.h"

const float HardwareStatusStore::GetLiquidTemp() const { return this->liquid_temp_; }
const int HardwareStatusStore::GetPumpSpeed() const { return this->pump_speed_; }
const int HardwareStatusStore::GetFanSpeed() const { return this->fan_speed_; }
void HardwareStatusStore::SetLiquidTemp(float liquid_temp) { this->liquid_temp_ = liquid_temp; }
void HardwareStatusStore::SetPumpSpeed(int pump_speed) { this->pump_speed_ = pump_speed; }
void HardwareStatusStore::SetFanSpeed(int fan_speed) { this->fan_speed_ = fan_speed; }
