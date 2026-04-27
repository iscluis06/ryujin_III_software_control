#include "states/select_memory_space_state.h"

#include <iostream>
#include <thread>

#include "libusb_wrapp.h"
#include "ryujin_device.h"

SelectMemorySpaceState::SelectMemorySpaceState(std::shared_ptr<libusb_device_handle *> device,
                                               int memory_index) : BaseState(device, this->kValidateResponse,
                                                                             sizeof(this->kValidateResponse)),
                                                                   memory_index_(memory_index) {
}

bool SelectMemorySpaceState::Execute() {
    LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
    auto buffer = LibUsbWrapp::FillArray(this->kSelectMemory, sizeof(this->kSelectMemory),
                                         RyujinDevice::kDefaultInterruptDataLength);
    buffer[4] = this->memory_index_;
    if (!wrapp.SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Failed to execute memory space instruction" << std::endl;
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
