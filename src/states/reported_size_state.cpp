#include "states/reported_size_state.h"

#include <cstring>
#include <iostream>
#include <thread>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

ReportedSizeState::ReportedSizeState(std::shared_ptr<libusb_device_handle *> device,
                                     std::vector<unsigned char> size) : BaseState(
                                                                          device, this->kValidateResponse,
                                                                          sizeof(this->kValidateResponse)),
                                                                        size_(size) {
}

bool ReportedSizeState::Execute() {
  LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
  auto buffer = LibUsbWrapp::FillArray(this->kReportedSize, sizeof(this->kReportedSize),
                                       RyujinDevice::kDefaultInterruptDataLength);
  memcpy(buffer.data() + 3, this->size_.data(), sizeof(unsigned char) * 3);
  if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
    std::cerr << "Failed to execute reported size instruction" << std::endl;
    return false;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
  if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
    std::cerr << "Failed to read from input endpoint" << std::endl;
    return false;
  }
  return this->IsMessageValid(response_back);
}
