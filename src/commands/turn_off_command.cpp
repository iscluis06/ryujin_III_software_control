#include "commands/turn_off_command.h"
#include "libusb_wrapp.h"
#include "ryujin_device.h"

TurnOffCommand::TurnOffCommand(std::shared_ptr<libusb_device_handle *> device)
    : BaseCommand(device) {}

bool TurnOffCommand::Execute() {
  auto buffer = LibUsbWrapp::FillArray(
      this->kTurnOff, 2, RyujinDevice::kDefaultInterruptDataLength);
  LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
  return wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
}
