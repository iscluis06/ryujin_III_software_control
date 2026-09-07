#include "commands/select_memory_space_command.h"

#include <iostream>
#include <thread>

#include "libusb_wrapper.h"
#include "ryujin_device.h"

SelectMemorySpaceCommand::SelectMemorySpaceCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index) :
    BaseCommand(std::move(wrapper), this->kValidateResponse, sizeof(this->kValidateResponse)),
    memory_index_(memory_index) {}

bool SelectMemorySpaceCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kSelectMemory, sizeof(this->kSelectMemory),
                                                RyujinDevice::kDefaultInterruptDataLength);
    buffer[4] = this->memory_index_;
    if (!this->GetWrapper()->SendInterrupt(RyujinDevice::kHidDeviceOut, buffer)) {
        std::cerr << "Failed to execute memory space instruction" << std::endl;
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
