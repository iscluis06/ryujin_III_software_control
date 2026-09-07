#include "commands/transaction_command.h"

#include <iostream>
#include <thread>

#include "libusb_wrapper.h"
#include "ryujin_device.h"

TransactionCommand::TransactionCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) :
    BaseCommand(std::move(wrapper), this->kValidateResponse, sizeof(this->kValidateResponse)) {}

bool TransactionCommand::Execute() {
    std::vector<unsigned char> buffer = this->GetWrapper()->FillArray(this->kTransaction, sizeof(this->kTransaction),
                                                                      RyujinDevice::kDefaultInterruptDataLength);
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Couldn't execute transaction instruction " << std::endl;
        return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
        std::cerr << "Failed to read from input endpoint" << std::endl;
        return false;
    }
    return this->IsMessageValid(response_back);
}
