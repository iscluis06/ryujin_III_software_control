#include "led_line/ryujin_liquid_temp_line.h"
#include "ryujin_device.h"

std::string RyujinLiquidTempLine::GetTitle() { return "Liquid Temp"; }
RyujinLiquidTempLine::RyujinLiquidTempLine(std::shared_ptr<HardwareStatusStore> store) : RyujinStatusLine(store) {}
std::string RyujinLiquidTempLine::GetLine() {
    return std::to_string(this->GetStore()->GetLiquidTemp()).substr(0, 5) + "\u2103";
}
