#include "commands/turn_on_command.h"
#include "ryujin_device.h"

TurnOnCommand::TurnOnCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {}

bool TurnOnCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kTurnOn, sizeof(this->kTurnOn),
                                                RyujinDevice::kDefaultInterruptDataLength);
    return this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
}
