#include "commands/upload_gif_command.h"

#include <cstring>
#include <iostream>

#include "libusb_wrapper.h"
#include "ryujin_device.h"

UploadGifCommand::UploadGifCommand(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                   std::shared_ptr<FileHandleBase> file_handle) :
    BaseCommand(std::move(wrapper), this->kValidateResponse, sizeof(this->kValidateResponse)) {
    this->file_handle_ = file_handle;
}

bool UploadGifCommand::Execute() {
    std::vector<unsigned char> buffer(RyujinDevice::kDefaultBulkLength, 0);
    for (int i = 0; i < this->file_handle_->GetIterations(); i++) {
        std::cout.flush();
        int current_size = this->file_handle_->GetSize() - ((i + 1) * RyujinDevice::kDefaultBulkLength);
        int size_to_copy =
                current_size < 0 ? current_size + RyujinDevice::kDefaultBulkLength : RyujinDevice::kDefaultBulkLength;
        memcpy(buffer.data(), this->file_handle_->GetBuffer().get() + (i * RyujinDevice::kDefaultBulkLength),
               sizeof(unsigned char) * size_to_copy);
        if (!this->GetWrapper()->SendBulk(RyujinDevice::kVendorDeviceOut, buffer)) {
            std::cout << "Failed to upload gif instruction [" << i << "/" << this->file_handle_->GetIterations() << "]"
                      << std::endl;
            return false;
        }
        std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
        if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
            std::cerr << "Failed to read from input endpoint" << std::endl;
            return false;
        }
        memset(buffer.data(), 0, RyujinDevice::kDefaultBulkLength);
        std::cout << "Upload porcentage: ";
        if (i + 1 < this->file_handle_->GetIterations()) {
            std::cout << (int) (100 * ((float) (i + 1) / (float) this->file_handle_->GetIterations())) << "%" << '\r';
        } else {
            std::cout << 100 << "%" << '\r' << std::endl;
        }
    }
    return true;
}
