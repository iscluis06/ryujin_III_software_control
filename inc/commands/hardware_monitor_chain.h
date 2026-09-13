#ifndef RYUJINIII_HARDWARE_MONITOR_CHAIN_H
#define RYUJINIII_HARDWARE_MONITOR_CHAIN_H
#include <list>
#include <memory>
#include "command_chain.h"
#include "led_line/led_line_factory.h"
#include "ryujin_constants.h"
#include "stores/hardware_status_store.h"

class HardwareMonitorChain : public CommandChain {
public:
    HardwareMonitorChain(
            std::shared_ptr<LibUsbWrapperBase> wrapper,
            RyujinConstants::MonitorMode mode = RyujinConstants::MonitorMode::PUNK,
            RyujinConstants::MonitorStyle style = RyujinConstants::MonitorStyle::STYLE01,
            LedLineFactory::LedLineImplementations line1 = LedLineFactory::LedLineImplementations::RYUJIN_LIQUID_TEMP);
    HardwareMonitorChain(std::shared_ptr<LibUsbWrapperBase> wrapper, RyujinConstants::MonitorMode mode,
                         RyujinConstants::MonitorStyle style, LedLineFactory::LedLineImplementations line1,
                         LedLineFactory::LedLineImplementations line2);
    HardwareMonitorChain(std::shared_ptr<LibUsbWrapperBase> wrapper, RyujinConstants::MonitorMode mode,
                         RyujinConstants::MonitorStyle style, LedLineFactory::LedLineImplementations line1,
                         LedLineFactory::LedLineImplementations line2, LedLineFactory::LedLineImplementations line3);
    bool Execute() override;
    static void StopLoop(int signal);
    std::shared_ptr<LedLineFactory> GetLedLineFactory();

private:
    // Thanks @BrandonKynoch for your findings
    // 0x0 = 1 line, 0x1 = 2 lines, 0x2 = 3 lines
    // I couldn't find any config for 4 lines on armoury create
    RyujinConstants::LinesConfig lines_config_ = RyujinConstants::LinesConfig::LINES1;
    static bool running_;
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
    std::shared_ptr<HardwareStatusStore> store_;
    std::shared_ptr<LedLineFactory> led_line_factory_;
    RyujinConstants::MonitorMode mode_;
    RyujinConstants::MonitorStyle style_;
    std::list<LedLineFactory::LedLineImplementations> lines_;
};
#endif // RYUJINIII_HARDWARE_MONITOR_CHAIN_H
