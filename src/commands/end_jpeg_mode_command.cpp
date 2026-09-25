#include "commands/end_jpeg_mode_command.h"
EndJpegModeCommand::EndJpegModeCommand(std::shared_ptr<LibUsbWrapperBase> base) : BaseCommand(base) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetInstruction(this->kEndJpegCommand);
    this->ShouldReadBack(true);
}
std::string EndJpegModeCommand::GetClassName() const { return "EndJpegModeCommand"; }
