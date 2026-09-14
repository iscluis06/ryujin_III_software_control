#include "commands/default_gif_command.h"
#include "ryujin_constants.h"

DefaultGifCommand::DefaultGifCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {
    this->SetInstruction(this->kDefaultGIFInstruction);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->ShouldReadBack(true);
}

std::string DefaultGifCommand::GetClassName() const { return "DefaultGifCommand"; }
