#include "led_line/led_line_factory.h"

#include "led_line/amd_core_line.h"
#include "led_line/git_last_commiter_line.h"
#include "led_line/ryujin_fan_speed_line.h"
#include "led_line/ryujin_liquid_temp_line.h"
#include "led_line/ryujin_pump_speed_line.h"

LedLineFactory::LedLineFactory(std::shared_ptr<HardwareStatusStore> store) : store_(store) {}
void LedLineFactory::SetGitPath(std::string path) { this->git_path_ = std::move(path); }
std::string LedLineFactory::PrintCurrentImplements() {
    std::stringstream ss;
    ss << "Current hardware monitor implementations:\n";
    ss << "0 - Ryujin Liquid Temp\n";
    ss << "1 - Ryujin Fan Speed\n";
    ss << "2 - Ryujin Pump Speed\n";
    ss << "3 - Amd Core Temp\n";
    ss << "4 - Git Last Commiter [param: path to git local repo]\n";
    return ss.str();
}
std::shared_ptr<LedLineBase> LedLineFactory::GetLedLine(LedLineImplementations implementation) {
    switch (implementation) {
        case LedLineImplementations::RYUJIN_LIQUID_TEMP:
            return std::make_shared<RyujinLiquidTempLine>(this->store_);
            break;
        case LedLineImplementations::RYUJIN_FAN_SPEED:
            return std::make_shared<RyujinFanSpeedLine>(this->store_);
            break;
        case LedLineImplementations::RYUJIN_PUMP_SPEED:
            return std::make_shared<RyujinPumpSpeedLine>(this->store_);
            break;
        case LedLineImplementations::AMD_CORE_TEMP:
            return std::make_shared<AmdCoreLine>();
            break;
        case LedLineImplementations::GIT_LAST_COMMITER:
            return std::make_shared<GitLastCommiterLine>(this->git_path_);
            break;
    }
    return nullptr;
}
