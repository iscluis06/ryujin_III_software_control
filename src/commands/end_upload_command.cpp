#include "commands/end_upload_command.h"

#include <iostream>
#include <thread>

#include "ryujin_constants.h"

EndUploadCommand::EndUploadCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {
    this->SetInstruction(this->kEndUpload);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string EndUploadCommand::GetClassName() const { return "EndUploadCommand"; }
