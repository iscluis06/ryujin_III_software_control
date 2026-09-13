#ifndef RYUJINIII_HARDWARE_MONITOR_CONFIG_H
#define RYUJINIII_HARDWARE_MONITOR_CONFIG_H
#include <vector>
#include "hardware_monitor_chain.h"
#include "led_line/led_line_factory.h"
#include "ryujin_constants.h"

class HardwareMonitorChainConfig {
public:
    HardwareMonitorChainConfig(std::shared_ptr<LibUsbWrapperBase> wrapper);
    void AddLine(int line);
    void SetMode(int mode);
    void SetStyle(int style);
    void SetGitPath(std::string git_path);
    std::shared_ptr<HardwareMonitorChain> GetChain();

private:
    std::vector<LedLineFactory::LedLineImplementations> lines_;
    RyujinConstants::MonitorMode mode_;
    RyujinConstants::MonitorStyle style_;
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
    std::string git_path_;
};

#endif // RYUJINIII_HARDWARE_MONITOR_CONFIG_H
