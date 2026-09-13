#include "ryujin_device.h"
#include <fstream>
#include <iostream>
#include <memory>
#include "ryujin_constants.h"

RyujinDevice::RyujinDevice(std::shared_ptr<LibUsbWrapperBase> wrapper) : wrapper_(wrapper) {}
RyujinDevice::~RyujinDevice() {
    if (!this->GetWrapper()->ReleaseInterface(RyujinConstants::kConfigInterface)) {
        std::cout << "Failed releasing config interface" << std::endl;
    }
    if (!this->GetWrapper()->ReleaseInterface(RyujinConstants::kLedInterface)) {
        std::cout << "Failed releasing LED interface" << std::endl;
    }
}

bool RyujinDevice::Initialize() {
    if (!this->GetWrapper()->InitializeDevice(RyujinConstants::kAsusDeviceId, RyujinConstants::kRyujinProductId)) {
        std::cout << "Device not found" << std::endl;
        return false;
    }
    if (!this->GetWrapper()->ClaimInterfaces(RyujinConstants::kConfigInterface) ||
        !this->GetWrapper()->ClaimInterfaces(RyujinConstants::kLedInterface)) {
        std::cout << "Failed claiming an interface " << std::endl;
        return false;
    }
    return true;
}
