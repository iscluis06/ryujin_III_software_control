#include "states/delete_state.h"

#include <iostream>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

DeleteState::DeleteState(std::shared_ptr<libusb_device_handle *> device) : BaseState(
    device, this->kValidateResponse, sizeof(this->kValidateResponse)) {
}

bool DeleteState::Execute() {
    LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
    auto buffer = LibUsbWrapp::FillArray(this->kDelete, sizeof(this->kDelete),
                                         RyujinDevice::kDefaultInterruptDataLength);
    if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Failed to execute delete memory instruction" << std::endl;
        return false;
    }
    std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
    if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
        std::cerr << "Failed to read from input endpoint" << std::endl;
        return false;
    }
    return this->IsMessageValid(response_back);
}
