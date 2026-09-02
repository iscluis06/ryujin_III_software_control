#include "commands/upload_gif_command.h"

#include <cstring>
#include <iostream>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

UploadGifCommand::UploadGifCommand(
    std::shared_ptr<libusb_device_handle *> device,
    const FileHandle &file_handle)
    : BaseCommand(device, this->kValidateResponse,
                  sizeof(this->kValidateResponse)),
      file_handle(file_handle) {}

bool UploadGifCommand::Execute() {
  LibUsbWrapp wrapp(this->GetDevice(), 0);
  std::vector<unsigned char> buffer(RyujinDevice::kDefaultBulkLength, 0);
  for (int i = 0; i < this->file_handle.iterations; i++) {
    std::cout.flush();
    int current_size =
        this->file_handle.size - ((i + 1) * RyujinDevice::kDefaultBulkLength);
    int size_to_copy = current_size < 0
                           ? current_size + RyujinDevice::kDefaultBulkLength
                           : RyujinDevice::kDefaultBulkLength;
    memcpy(buffer.data(),
           this->file_handle.buffer.get() +
               (i * RyujinDevice::kDefaultBulkLength),
           sizeof(unsigned char) * size_to_copy);
    if (!wrapp.SendBulk(RyujinDevice::kVendorDeviceOut, buffer)) {
      std::cout << "Failed to upload gif instruction [" << i << "/"
                << this->file_handle.iterations << "]" << std::endl;
      return false;
    }
    std::vector<unsigned char> response_back(
        RyujinDevice::kDefaultInterruptDataLength, 0);
    if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
      std::cerr << "Failed to read from input endpoint" << std::endl;
      return false;
    }
    memset(buffer.data(), 0, RyujinDevice::kDefaultBulkLength);
    std::cout << "Upload porcentage: ";
    if (i + 1 < this->file_handle.iterations) {
      std::cout << (int)(100 *
                         ((float)(i + 1) / (float)this->file_handle.iterations))
                << "%" << '\r';
    } else {
      std::cout << 100 << "%" << '\r' << std::endl;
    }
  }
  return true;
}
