#include "ryujin_device.h"
#include <fstream>
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>

#include "libusb_wrapp.h"
#include "states/select_gif_state.h"
#include "states/turn_off_state.h"
#include "states/turn_on_state.h"
#include "states/delete_chain.h"
#include "states/upload_chain.h"

RyujinDevice::RyujinDevice() {
    libusb_init(nullptr);
    this->device = std::make_shared<libusb_device_handle *>();
    this->GetDevice();
    if (this->device) {
        lusb_ = std::make_unique<LibUsbWrapp>(this->device, this->kDefaultTimeOut);
        libusb_set_auto_detach_kernel_driver(*(this->device.get()), 1);
        libusb_set_configuration(*(this->device.get()), 1);
        libusb_claim_interface(*(this->device.get()), 0);
        libusb_claim_interface(*(this->device.get()), 1);
        libusb_clear_halt(*(this->device.get()), RyujinDevice::kVendorDeviceOut);
        libusb_clear_halt(*(this->device.get()), RyujinDevice::kHidDeviceOut);
        libusb_clear_halt(*(this->device.get()), RyujinDevice::kVendorDeviceIn);
        libusb_clear_halt(*(this->device.get()), RyujinDevice::kHidDeviceIn);
    } else {
        std::cerr << "Device not found, exiting..." << std::endl;
        exit(0);
    }
}

RyujinDevice::~RyujinDevice() {
    if (device != nullptr) {
        libusb_release_interface(*this->device.get(), this->kConfigInterface);
        libusb_release_interface(*this->device.get(), this->kLedInterface);
        libusb_close(*this->device.get());
    }
}

void RyujinDevice::Reset() const {
    libusb_reset_device(*this->device.get());
}

void RyujinDevice::GetDevice() {
    libusb_device **dev_list = nullptr;
    ssize_t result_device_list = libusb_get_device_list(nullptr, &dev_list);
    for (int i = 0; i < result_device_list; i++) {
        std::shared_ptr<libusb_device_descriptor> desc = std::make_shared<libusb_device_descriptor>();
        libusb_get_device_descriptor(dev_list[i], desc.get());
        if (desc->idVendor == this->kAsusDeviceId && desc->idProduct == this->kRyujinProductId) {
            libusb_open(dev_list[i], (this->device.get()));
            libusb_reset_device(*(this->device.get()));
            libusb_open(dev_list[i], (this->device.get()));
            break;
        }
    }
    libusb_free_device_list(dev_list, 1);
}

void RyujinDevice::TurnOnLedDisplay() const {
    TurnOnState turn_on_state(this->device);
    turn_on_state.Execute();
};

void RyujinDevice::TurnOffLedDisplay() const {
    TurnOffState turn_off_state(this->device);
    turn_off_state.Execute();
}

void RyujinDevice::SelectGifFromMemory(int memory_index) const {
    SelectGifState select_gif_state(this->device, memory_index);
    select_gif_state.Execute();
}

void RyujinDevice::DeleteFromMemory(int memory_index) const {
    DeleteChain delete_chain(this->device, memory_index);
    delete_chain.Execute();
}

void RyujinDevice::UploadGif(const std::string &path, short memory_space) {
    UploadChain upload_chain(this->device, path, memory_space);
    upload_chain.Execute();
};


