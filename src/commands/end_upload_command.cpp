#include "commands/end_upload_command.h"

#include <iostream>
#include <thread>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

EndUploadCommand::EndUploadCommand(
    std::shared_ptr<libusb_device_handle *> device)
    : BaseCommand(device, this->kValidateResponse,
                  sizeof(this->kValidateResponse)) {}

bool EndUploadCommand::Execute() {
  LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
  auto buffer =
      LibUsbWrapp::FillArray(this->kEndUpload, sizeof(this->kEndUpload),
                             RyujinDevice::kDefaultInterruptDataLength);
  if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
    std::cerr << "Failed to execute end upload instruction" << std::endl;
    return false;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  std::vector<unsigned char> response_back(
      RyujinDevice::kDefaultInterruptDataLength, 0);
  if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
    std::cerr << "Failed to read from input endpoint" << std::endl;
    return false;
  }
  return this->IsMessageValid(response_back);
}
