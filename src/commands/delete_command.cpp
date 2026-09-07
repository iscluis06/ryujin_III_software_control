#include "commands/delete_command.h"

#include <iostream>

#include "libusb_wrapper.h"
#include "ryujin_device.h"

DeleteCommand::DeleteCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) :
    BaseCommand(std::move(wrapper), this->kValidateResponse, sizeof(this->kValidateResponse)) {}

bool DeleteCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kDelete, sizeof(this->kDelete),
                                                RyujinDevice::kDefaultInterruptDataLength);
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Failed to execute delete memory instruction" << std::endl;
        return false;
    }
    std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
        std::cerr << "Failed to read from input endpoint" << std::endl;
        return false;
    }
    return this->IsMessageValid(response_back);
}
