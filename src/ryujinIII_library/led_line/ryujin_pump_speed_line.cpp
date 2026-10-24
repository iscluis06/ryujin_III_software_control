#include "led_line/ryujin_pump_speed_line.h"
RyujinPumpSpeedLine::RyujinPumpSpeedLine(std::shared_ptr<HardwareStatusStore> store) : RyujinStatusLine(store) {}
std::string RyujinPumpSpeedLine::GetLine() {
    return std::to_string(this->GetStore()->GetPumpSpeed()).substr(0, 5) + " rpm";
}
std::string RyujinPumpSpeedLine::GetTitle() { return "Pump Speed"; }
std::string RyujinPumpSpeedLine::GetClassName() { return "RyujinPumpSpeedLine"; }
