#include "commands/default_gif.h"
#include "libusb_wrapper.h"
#include "ryujin_device.h"

DefaultGif::DefaultGif(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {}

bool DefaultGif::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kDefaultGIFInstruction, sizeof(this->kDefaultGIFInstruction),
                                                RyujinDevice::kDefaultInterruptDataLength);
    bool result = this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
    std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
    this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceIn, response_back);
    return result;
}
