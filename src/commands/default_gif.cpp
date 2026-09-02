#include "commands/default_gif.h"
#include "libusb_wrapp.h"
#include "ryujin_device.h"

DefaultGif::DefaultGif(std::shared_ptr<libusb_device_handle *> device)
    : BaseCommand(device) {}

bool DefaultGif::Execute() {
  LibUsbWrapp wrapp = LibUsbWrapp(this->GetDevice(), this->kTimeout);
  auto buffer = wrapp.FillArray(this->kDefaultGIFInstruction,
                                sizeof(this->kDefaultGIFInstruction),
                                RyujinDevice::kDefaultInterruptDataLength);
  bool result = wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
  std::vector<unsigned char> response_back(
      RyujinDevice::kDefaultInterruptDataLength, 0);
  wrapp.SendInterrupt(RyujinDevice::kHidDeviceIn, response_back);
  return result;
}
