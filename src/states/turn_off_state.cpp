#include "states/turn_off_state.h"
#include "libusb_wrapp.h"
#include "ryujin_device.h"

TurnOffState::TurnOffState(std::shared_ptr<libusb_device_handle *> device) : BaseState(device) {}

bool TurnOffState::Execute() {
    auto buffer = LibUsbWrapp::FillArray(this->kTurnOff, 2, RyujinDevice::kDefaultInterruptDataLength);
    LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
    return wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
}
