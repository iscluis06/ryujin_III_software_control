#include "commands/start_upload_command.h"

#include <iostream>
#include <thread>

#include "ryujin_constants.h"

StartUploadCommand::StartUploadCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {
    this->SetInstruction(this->kStartUpload);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string StartUploadCommand::GetClassName() const { return "StartUploadCommand"; }
