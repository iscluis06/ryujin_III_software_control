#include "states/turn_on_state.h"
#include "ryujin_device.h"

TurnOnState::TurnOnState(std::shared_ptr<libusb_device_handle *> device): BaseState(device) {

}

bool TurnOnState::Execute() {
    LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
    auto buffer = LibUsbWrapp::FillArray(this->kTurnOn, sizeof(this->kTurnOn), RyujinDevice::kDefaultInterruptDataLength);
    return wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer);
}