#include "commands/turn_off_command.h"
#include "ryujin_constants.h"

TurnOffCommand::TurnOffCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(wrapper) {
    this->SetInstruction(this->GetWrapper()->FillArray(this->kTurnOff.data(), this->kTurnOff.size(),
                                                       RyujinConstants::kDefaultInterruptDataLength));
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->ShouldReadBack(true);
}

std::string TurnOffCommand::GetClassName() const { return "TurnOffCommand"; }
