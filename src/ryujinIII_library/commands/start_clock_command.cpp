#include "commands/start_clock_command.h"
StartClockCommand::StartClockCommand(std::shared_ptr<LibUsbWrapperBase> base) : BaseCommand(std::move(base)) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->ShouldReadBack(true);
    this->SetInstruction(kInstruction);
}
std::string StartClockCommand::GetClassName() const { return "StartClockCommand"; }
