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

// bool StartHardwareMonitorCommand::Execute() {
//     std::vector<unsigned char> buffer = this->GetWrapper()->FillArray(
//             this->kHardwareMonitor, sizeof(this->kHardwareMonitor),
//             RyujinDevice::kDefaultInterruptDataLength);
//     bool result = this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
//     if (!result) {
//         std::cerr << "Couldn't execute start transaction instruction " << std::endl;
//         return result;
//     }
//     std::this_thread::sleep_for(std::chrono::milliseconds(50));
//     std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
//     if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
//         std::cerr << "Failed to read from input endpoint" << std::endl;
//         return false;
//     }
//     return result;
// }
