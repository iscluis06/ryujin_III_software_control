#include "commands/select_gif_command.h"

#include <iostream>
#include <thread>

#include "ryujin_constants.h"

SelectGifCommand::SelectGifCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index) :
    BaseCommand(std::move(wrapper)) {
    auto buffer = this->GetWrapper()->FillArray(this->kSelectGif.data(), this->kSelectGif.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    buffer[4] = memory_index;
    this->SetInstruction(buffer);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string SelectGifCommand::GetClassName() const { return "SelectGifCommand"; }
