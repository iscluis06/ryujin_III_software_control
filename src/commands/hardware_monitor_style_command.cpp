#include "commands/hardware_monitor_style_command.h"

#include "ryujin_constants.h"
HardwareMonitorStyleCommand::HardwareMonitorStyleCommand(const std::shared_ptr<LibUsbWrapperBase> &wrapper, int lines,
                                                         int mode, int style) : BaseCommand(wrapper) {
    auto buffer = this->GetWrapper()->FillArray(this->kHardwareMonitor.data(), this->kHardwareMonitor.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    buffer[this->kNumLinesOffset] = lines;
    buffer[this->kModeByteOffset] = mode;
    buffer[this->kStyleOffset] = style;
    this->SetInstruction(buffer);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->ShouldReadBack(true);
}
