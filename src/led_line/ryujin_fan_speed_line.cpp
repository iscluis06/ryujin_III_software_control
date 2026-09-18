#include "led_line/ryujin_fan_speed_line.h"
RyujinFanSpeedLine::RyujinFanSpeedLine(std::shared_ptr<HardwareStatusStore> store) : RyujinStatusLine(store) {}
std::string RyujinFanSpeedLine::GetLine() {
    return std::to_string(this->GetStore()->GetFanSpeed()).substr(0, 5) + " rpm";
}
std::string RyujinFanSpeedLine::GetTitle() { return "Fan Speed"; }
std::string RyujinFanSpeedLine::GetClassName() { return "RyujinFanSpeedLine"; }
