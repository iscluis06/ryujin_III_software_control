#include "commands/turn_on_command.h"
#include "ryujin_constants.h"

TurnOnCommand::TurnOnCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {
    this->SetInstruction(this->kTurnOn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->ShouldReadBack(true);
}

std::string TurnOnCommand::GetClassName() const { return "TurnOnCommand"; }
