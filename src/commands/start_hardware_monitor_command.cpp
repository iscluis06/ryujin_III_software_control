#include "commands/start_hardware_monitor_command.h"

#include "ryujin_constants.h"

StartHardwareMonitorCommand::StartHardwareMonitorCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) :
    BaseCommand(std::move(wrapper)) {
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->ShouldReadBack(true);
    this->SetInstruction(this->kHardwareMonitor);
}
std::string StartHardwareMonitorCommand::GetClassName() const { return "StartHardwareMonitorCommand"; }
