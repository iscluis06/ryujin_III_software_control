#include "commands/turn_on_command.h"
#include "ryujin_device.h"

TurnOnCommand::TurnOnCommand(std::shared_ptr<libusb_device_handle *> device)
    : BaseCommand(device) {}

bool TurnOnCommand::Execute() {
  LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
  auto buffer =
      LibUsbWrapp::FillArray(this->kTurnOn, sizeof(this->kTurnOn),
                             RyujinDevice::kDefaultInterruptDataLength);
  return wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
}