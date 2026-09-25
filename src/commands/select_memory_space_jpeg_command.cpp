#include "commands/select_memory_space_jpeg_command.h"

#include <iostream>

#include "ryujin_constants.h"

SelectMemorySpaceJPEGCommand::SelectMemorySpaceJPEGCommand(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                                           int memory_index) : BaseCommand(std::move(wrapper)) {
    auto buffer = this->GetWrapper()->FillArray(this->kSelectMemory.data(), this->kSelectMemory.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    buffer[this->kJpegIndex] = memory_index;
    this->SetInstruction(buffer);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string SelectMemorySpaceJPEGCommand::GetClassName() const { return "SelectMemorySpaceCommand"; }
