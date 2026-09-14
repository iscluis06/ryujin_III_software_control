#include "commands/hardware_monitor_chain.h"
#include <csignal>
#include <iostream>
#include <thread>

#include "commands/hardware_monitor_line_command.h"
#include "commands/hardware_monitor_style_command.h"
#include "commands/hardware_status_command.h"
#include "commands/start_hardware_monitor_command.h"
#include "led_line/led_line_factory.h"
#include "wrappers/libusb_wrapper.h"

bool HardwareMonitorChain::running_ = false;
HardwareMonitorChain::HardwareMonitorChain(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                           RyujinConstants::MonitorMode mode, RyujinConstants::MonitorStyle style,
                                           LedLineFactory::LedLineImplementations line1) :
    mode_(mode), wrapper_(std::move(wrapper)), style_(style) {
    this->store_ = std::make_shared<HardwareStatusStore>();
    this->led_line_factory_ = std::make_shared<LedLineFactory>(this->store_);
    this->lines_.push_back(line1);
    this->lines_config_ = RyujinConstants::LinesConfig::LINES1;
}
HardwareMonitorChain::HardwareMonitorChain(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                           RyujinConstants::MonitorMode mode, RyujinConstants::MonitorStyle style,
                                           LedLineFactory::LedLineImplementations line1,
                                           LedLineFactory::LedLineImplementations line2) :
    HardwareMonitorChain(std::move(wrapper), mode, style, line1) {
    this->lines_.push_back(line2);
    this->lines_config_ = RyujinConstants::LinesConfig::LINES2;
}
HardwareMonitorChain::HardwareMonitorChain(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                           RyujinConstants::MonitorMode mode, RyujinConstants::MonitorStyle style,
                                           LedLineFactory::LedLineImplementations line1,
                                           LedLineFactory::LedLineImplementations line2,
                                           LedLineFactory::LedLineImplementations line3) :
    HardwareMonitorChain(std::move(wrapper), mode, style, line1, line2) {
    this->lines_.push_back(line3);
    this->lines_config_ = RyujinConstants::LinesConfig::LINES3;
}

bool HardwareMonitorChain::Execute() {
    signal(SIGINT, HardwareMonitorChain::StopLoop);
    auto start_hardware_monitor_mode = std::make_shared<StartHardwareMonitorCommand>(this->wrapper_);
    auto hardware_monitor_style = std::make_shared<HardwareMonitorStyleCommand>(
            this->wrapper_, static_cast<int>(this->lines_config_), static_cast<int>(this->mode_),
            static_cast<int>(this->style_));
    start_hardware_monitor_mode->Execute();
    hardware_monitor_style->Execute();
    HardwareMonitorChain::running_ = true;

    while (HardwareMonitorChain::running_) {
        HardwareStatusCommand status(this->wrapper_, this->store_);
        status.Execute();
        int i = 0;
        for (auto line: this->lines_) {
            HardwareMonitorLineCommand line_command(this->wrapper_, this->led_line_factory_->GetLedLine(line), i);
            i++;
            line_command.Execute();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return true;
}
void HardwareMonitorChain::StopLoop(int signal) {
    std::cout << "Stopping loop" << std::endl;
    HardwareMonitorChain::running_ = false;
}
std::shared_ptr<LedLineFactory> HardwareMonitorChain::GetLedLineFactory() { return this->led_line_factory_; }
