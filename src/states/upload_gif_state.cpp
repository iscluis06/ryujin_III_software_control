#include "states/upload_gif_state.h"

#include <cstring>
#include <iostream>
#include <thread>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

UploadGifState::UploadGifState(std::shared_ptr<libusb_device_handle *> device,
                               const FileHandle &file_handle) : BaseState(
                                                                    device, this->kValidateResponse,
                                                                    sizeof(this->kValidateResponse)),
                                                                file_handle(file_handle) {
}

bool UploadGifState::Execute() {
    LibUsbWrapp wrapp(this->GetDevice(), 0);
    std::vector<unsigned char> buffer(RyujinDevice::kDefaultBulkLength, 0);
    libusb_clear_halt(*(this->GetDevice()), RyujinDevice::kHidDeviceIn);
    for (int i = 0; i < this->file_handle.iterations; i++) {
        std::cout << "Upload porcentage: " << 100 * ((float) (i + 1) / (float) this->file_handle.iterations) << "%" <<
                '\r';
        std::cout.flush();
        memcpy(buffer.data(), this->file_handle.buffer.get() + (i * RyujinDevice::kDefaultBulkLength),
               sizeof(unsigned char) * RyujinDevice::kDefaultBulkLength);
        if (!wrapp.SendBulk(RyujinDevice::kVendorDeviceOut, buffer)) {
            std::cerr << "Failed to upload gif instruction [" << i << "/" << this->file_handle.iterations << "]" <<
                    std::endl;
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
        if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
            std::cerr << "Failed to read from input endpoint" << std::endl;
            return false;
        }
        if (!this->IsMessageValid(response_back)) {
            return false;
        }
    }
    return true;
}

