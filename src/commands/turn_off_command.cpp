#include "commands/turn_off_command.h"
#include "libusb_wrapper.h"
#include "ryujin_device.h"

TurnOffCommand::TurnOffCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(wrapper) {}

bool TurnOffCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kTurnOff, 2, RyujinDevice::kDefaultInterruptDataLength);
    return this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
}
