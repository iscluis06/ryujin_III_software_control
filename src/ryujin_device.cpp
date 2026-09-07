#include "ryujin_device.h"
#include <fstream>
#include <iostream>
#include <memory>

RyujinDevice::RyujinDevice(std::shared_ptr<LibUsbWrapper> wrapper) : wrapper_(wrapper) {}
RyujinDevice::~RyujinDevice() {
    if (!this->GetWrapper()->ReleaseInterface(this->kConfigInterface)) {
        std::cout << "Failed releasing config interface" << std::endl;
    }
    if (!this->GetWrapper()->ReleaseInterface(this->kLedInterface)) {
        std::cout << "Failed releasing LED interface" << std::endl;
    }
}

bool RyujinDevice::Initialize() {
    if (!this->GetWrapper()->InitializeDevice(this->kAsusDeviceId, this->kRyujinProductId)) {
        std::cout << "Device not found" << std::endl;
        return false;
    }
    if (!this->GetWrapper()->ClaimInterfaces(kConfigInterface) || !this->GetWrapper()->ClaimInterfaces(kLedInterface)) {
        std::cout << "Failed claiming an interface " << std::endl;
        return false;
    }
    return true;
}
