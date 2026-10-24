#include "commands/start_transaction_command.h"

#include <thread>

#include "ryujin/ryujin_constants.h"

StartTransactionCommand::StartTransactionCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) :
    BaseCommand(std::move(wrapper)) {
    this->SetInstruction(this->kStartTransaction);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string StartTransactionCommand::GetClassName() const { return "StartTransactionCommand"; }
