#include "commands/turn_off_command.h"
#include "ryujin_constants.h"

TurnOffCommand::TurnOffCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {
    this->SetInstruction(this->kTurnOff);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->ShouldReadBack(true);
}

std::string TurnOffCommand::GetClassName() const { return "TurnOffCommand"; }
