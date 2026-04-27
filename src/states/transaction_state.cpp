#include "states/transaction_state.h"

#include <iostream>
#include <thread>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

TransactionState::TransactionState(std::shared_ptr<libusb_device_handle *> device) : BaseState(
    device, this->kValidateResponse, sizeof(this->kValidateResponse)) {
}

bool TransactionState::Execute() {
    LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
    std::vector<unsigned char> buffer = LibUsbWrapp::FillArray(this->kTransaction, sizeof(this->kTransaction),
                                                               RyujinDevice::kDefaultInterruptDataLength);
    if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Couldn't execute transaction instruction " << std::endl;
        return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
    if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
        std::cerr << "Failed to read from input endpoint" << std::endl;
        return false;
    }
    return this->IsMessageValid(response_back);
}
