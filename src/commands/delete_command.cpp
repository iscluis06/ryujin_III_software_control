#include "commands/delete_command.h"

#include <iostream>

#include "ryujin_constants.h"

DeleteCommand::DeleteCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {
    this->SetInstruction(this->kDelete);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetValidationMessage(this->kValidateResponse);
    this->ShouldReadBack(true);
}

std::string DeleteCommand::GetClassName() const { return "DeleteCommand"; }
