#include "commands/transaction_command.h"

#include <iostream>
#include <thread>

#include "ryujin_constants.h"

TransactionCommand::TransactionCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {
    this->SetInstruction(kTransaction);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string TransactionCommand::GetClassName() const { return "TransactionCommand"; }
