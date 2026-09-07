#include "commands/reported_size_command.h"

#include <cstring>
#include <iostream>
#include <thread>

#include "libusb_wrapper.h"
#include "ryujin_device.h"

ReportedSizeCommand::ReportedSizeCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, std::vector<unsigned char> size) :
    BaseCommand(std::move(wrapper), this->kValidateResponse, sizeof(this->kValidateResponse)), size_(size) {}

bool ReportedSizeCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kReportedSize, sizeof(this->kReportedSize),
                                                RyujinDevice::kDefaultInterruptDataLength);
    memcpy(buffer.data() + 3, this->size_.data(), sizeof(unsigned char) * 3);
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Failed to execute reported size instruction" << std::endl;
        return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::vector<unsigned char> response_back(RyujinDevice::kDefaultInterruptDataLength, 0);
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceIn, response_back)) {
        std::cerr << "Failed to read from input endpoint" << std::endl;
        return false;
    }
    return this->IsMessageValid(response_back);
}
