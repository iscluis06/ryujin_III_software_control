#include "commands/slide_show_jpeg_mode_command.h"

SlideShowJpegModeCommand::SlideShowJpegModeCommand(std::shared_ptr<LibUsbWrapperBase> base) :
    BaseCommand(std::move(base)) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetInstruction(this->kInstruction);
}
std::string SlideShowJpegModeCommand::GetClassName() const { return "SlideShowJpegModeCommand"; }
