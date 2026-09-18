#include "commands/upload_gif_command.h"

#include <cstring>
#include <iostream>

#include "ryujin_constants.h"

UploadGifCommand::UploadGifCommand(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                   std::shared_ptr<FileHandleBase> file_handle) : BaseCommand(std::move(wrapper)) {
    this->file_handle_ = file_handle;
}

bool UploadGifCommand::Execute() {
    std::vector<unsigned char> buffer(RyujinConstants::kDefaultBulkLength, 0);
    for (int i = 0; i < this->file_handle_->GetIterations(); i++) {
        int current_size = this->file_handle_->GetSize() - ((i + 1) * RyujinConstants::kDefaultBulkLength);
        int size_to_copy = current_size < 0 ? current_size + RyujinConstants::kDefaultBulkLength
                                            : RyujinConstants::kDefaultBulkLength;
        memcpy(buffer.data(), this->file_handle_->GetBuffer().get() + (i * RyujinConstants::kDefaultBulkLength),
               sizeof(unsigned char) * size_to_copy);
        if (!this->GetWrapper()->SendBulk(RyujinConstants::kVendorDeviceOut, buffer)) {
            std::cout << "Failed to upload gif instruction [" << i << "/" << this->file_handle_->GetIterations() << "]"
                      << std::endl;
            return false;
        }
        std::vector<unsigned char> response_back(RyujinConstants::kDefaultInterruptDataLength, 0);
        if (!this->GetWrapper()->SendInterrupt(RyujinConstants::kHidDeviceIn, response_back)) {
            std::cerr << "Failed to read from input endpoint" << std::endl;
            return false;
        }
        memset(buffer.data(), 0, RyujinConstants::kDefaultBulkLength);
        std::cout << "\rUpload porcentage: ";
        if (i + 1 < this->file_handle_->GetIterations()) {
            std::cout << (int) (100 * ((float) (i + 1) / (float) this->file_handle_->GetIterations())) << "%"
                      << std::flush;
        } else {
            std::cout << 100 << "%" << std::flush;
        }
    }
    std::cout << std::endl;
    return true;
}

std::string UploadGifCommand::GetClassName() const { return "UploadGifCommand"; }
