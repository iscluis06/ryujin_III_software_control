#include "commands/start_upload_command.h"

#include <iostream>
#include <thread>

#include "libusb_wrapper.h"
#include "ryujin_device.h"

StartUploadCommand::StartUploadCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) :
    BaseCommand(std::move(wrapper), this->kValidateResponse, sizeof(this->kValidateResponse)) {}

bool StartUploadCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kStartUpload, sizeof(this->kStartUpload),
                                                RyujinDevice::kDefaultInterruptDataLength);
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Failed to execute start upload instruction" << std::endl;
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
