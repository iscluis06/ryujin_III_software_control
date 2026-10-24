#include "commands/show_jpeg_command.h"

ShowJpegCommand::ShowJpegCommand(std::shared_ptr<LibUsbWrapperBase> base, int index) : BaseCommand(base) {
    auto buffer = this->GetWrapper()->FillArray(this->kShowJpegCommand.data(), this->kShowJpegCommand.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    buffer[this->kShowJpegIndex] = index;
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetInstruction(buffer);
    this->ShouldReadBack(true);
}
std::string ShowJpegCommand::GetClassName() const { return "ShowJpegCommand"; }
