#include "states/start_upload_state.h"

#include <iostream>
#include <thread>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

StartUploadState::StartUploadState(std::shared_ptr<libusb_device_handle *> device) : BaseState(
    device, this->kValidateResponse, sizeof(this->kValidateResponse)) {
}

bool StartUploadState::Execute() {
    LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
    auto buffer = LibUsbWrapp::FillArray(this->kStartUpload, sizeof(this->kStartUpload),
                                         RyujinDevice::kDefaultInterruptDataLength);
    if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Failed to execute start upload instruction" << std::endl;
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
