#include "commands/select_jpeg_command.h"

#include <iostream>
#include <thread>

#include "ryujin_constants.h"

SelectJpegCommand::SelectJpegCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index) :
    BaseCommand(std::move(wrapper)) {
    auto buffer = this->GetWrapper()->FillArray(this->kSelectJpeg.data(), this->kSelectJpeg.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    buffer[this->kJpegIndex] = memory_index;
    this->SetInstruction(buffer);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
}

std::string SelectJpegCommand::GetClassName() const { return "SelectJpegCommand"; }
