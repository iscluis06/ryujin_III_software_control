#include "commands/start_jpeg_selection_command.h"
StartJpegSelectionCommand::StartJpegSelectionCommand(std::shared_ptr<LibUsbWrapperBase> base) : BaseCommand(base) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetInstruction(kStartJpegSelectionCommand);
    this->ShouldReadBack(true);
}
std::string StartJpegSelectionCommand::GetClassName() const { return "StartJpegSelectionCommand"; }
