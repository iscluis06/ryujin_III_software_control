#include "commands/reported_size_command.h"

#include <iostream>
#include <thread>

#include "ryujin_constants.h"

ReportedSizeCommand::ReportedSizeCommand(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                         const std::vector<unsigned char> &size) : BaseCommand(std::move(wrapper)) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    auto buffer = this->GetWrapper()->FillArray(this->kReportedSize.data(), this->kReportedSize.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    buffer[3] = size[0];
    buffer[4] = size[1];
    buffer[5] = size[2];
    this->SetInstruction(buffer);
    this->SetTimeout(50);
    this->ShouldReadBack(true);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string ReportedSizeCommand::GetClassName() const { return "ReportedSizeCommand"; }
