#include "ryujin_device.h"
#include <cstring>
#include <fstream>
#include <cmath>
#include <array>
#include <iostream>
#include <memory>
#include <thread>

#include "libusb_wrapp.h"

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
        libusb_clear_halt(*(this->device.get()), 0x01);
        libusb_clear_halt(*(this->device.get()), 0x02);
        libusb_clear_halt(*(this->device.get()), 0x81);
        libusb_clear_halt(*(this->device.get()), 0x82);
        std::vector<unsigned char> buffer = std::vector<unsigned char>(255);
        this->lusb_->SendControl(0x80, 8, 0x0000, 0, buffer, 1);
        this->lusb_->SendControl(0x80, 6, 0x0300, 0x0409, buffer, 4);
        this->lusb_->SendControl(0x80, 6, 0x0302, 0x0409, buffer, 255);
        this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 8);
        this->lusb_->SendControl(0x80, 6, 0x0200, 0x0000, buffer, 9);
        this->lusb_->SendControl(0x80, 6, 0x0200, 0x0000, buffer, 64);
        this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 18);
        this->lusb_->SendControl(0x80, 6, 0x0200, 0x0000, buffer, 64);
        this->lusb_->SendControl(0x80, 6, 0x0303, 0x0409, buffer, 255);
        this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 64);
        this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 18);
        this->lusb_->SendControl(0x21, 0x0a, 0x0000, 1, buffer, 0);
    }else {
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

void RyujinDevice::Reset() {
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
            break;
        }
    }
    libusb_free_device_list(dev_list, 1);
}

void RyujinDevice::TurnOnLedDisplay() {
    this->lusb_->SendInterrupt(this->kHidDeviceOut, this->FillArray(this->kTurnOn, 3, this->kDefaultInterruptDataLength));
};

void RyujinDevice::TurnOffLedDisplay() {
    this->lusb_->SendInterrupt(this->kHidDeviceOut, this->FillArray(this->kTurnOff, 2, this->kDefaultInterruptDataLength));
}

void RyujinDevice::SelectGifFromMemory(int memory_index) {
    std::vector<unsigned char> buffer = FillArray(this->kSelectGif, sizeof(this->kSelectGif), this->kDefaultInterruptDataLength);
    buffer[4] = memory_index;
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
}

void RyujinDevice::DeleteFromMemory(int memory_index) {
    this->SelectGifFromMemory(memory_index);
    std::vector<unsigned char> buffer = FillArray(this->kDelete, sizeof(this->kDelete), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
}

void RyujinDevice::UploadGif(std::string path) {
    std::vector<unsigned char> buffer_response = this->FillArray(nullptr, 0, this->kDefaultInterruptDataLength);
    std::vector<unsigned char> buffer = this->FillArray(this->kTransaction, sizeof(this->kTransaction), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    this->lusb_->SendInterrupt(0x82, buffer_response);

    buffer = this->FillArray(this->kStartTransaction, sizeof(this->kStartTransaction), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    this->lusb_->SendInterrupt(0x82, buffer_response);

    buffer = this->FillArray(this->kSelectMemory, sizeof(this->kSelectMemory), this->kDefaultInterruptDataLength);
    buffer[4] = 0x05;
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    // libusb_interrupt_transfer(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength,
        // nullptr, this->kDefaultTimeOut);

    buffer = this->FillArray(this->kStartUpload, sizeof(this->kStartUpload), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    this->lusb_->SendInterrupt(0x82, buffer_response);

    std::shared_ptr<RyujinDevice::FileHandle> file_handle = this->ReadFile(path);
    int iterations = std::ceil(file_handle->size/4096.0f);
    // std::array<unsigned char,3> size_array = GetSizeToHex(file_handle->size);
    // std::array<unsigned char,3> size_array = GetSizeToHex(iterations*4096);
    // buffer = this->FillArray(this->kReportedSize, sizeof(this->kReportedSize), this->kDefaultInterruptDataLength);
    // memcpy(buffer+3, size_array.data(), sizeof(unsigned char)*3);
    const unsigned char fixed_size_test[6] = {0xec, 0x7f, 0x02, 0x04, 0x19, 0x21};
    buffer = this->FillArray(fixed_size_test, sizeof(fixed_size_test), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    this->lusb_->SendInterrupt(0x82, buffer_response);

    buffer.reserve(4096);
    for (int i=0; i<iterations; i++) {
        buffer.clear();
        memcpy(buffer.data(),file_handle->buffer.get()+(i*4096),4096);
        this->lusb_->SendBulk(this->kVendorDeviceOut, buffer);
        this->lusb_->SendInterrupt(0x82, buffer_response);
    }

    buffer = this->FillArray(this->kEndUpload, sizeof(this->kEndUpload), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    this->lusb_->SendInterrupt(0x82, buffer_response);
    this->SelectGifFromMemory(0x02);

};

std::vector<unsigned char> RyujinDevice::FillArray(const unsigned char *array, int array_size, int desired_size) {
    std::vector<unsigned char> buffer(desired_size, 0);
    for ( int i = 0; i<array_size; i++) {
        buffer.at(i) = array[i];
    }
    return buffer;
}

std::array<unsigned char, 3> RyujinDevice::GetSizeToHex(int size) {
    std::array<unsigned char, 3> array_size = {0};
    int i = 0;
    int value = size;
    while (true) {
        int hex_val = value%16;
        if (array_size[i/2] == 0) {
            array_size[i/2] += hex_val;
        }else {
            array_size[i/2] += hex_val*16;
        }
        value = value/16;
        i++;
        if (i>5) {
            break;
        }
    }
    return array_size;
}

std::shared_ptr<RyujinDevice::FileHandle> RyujinDevice::ReadFile(std::string path) {
    std::ifstream file(path, std::ios::in|std::ios::binary|std::ios::ate);
    std::shared_ptr<RyujinDevice::FileHandle> file_handle = std::make_shared<RyujinDevice::FileHandle>();
    if ( file.is_open()) {
        file_handle->size = file.tellg();
        file_handle->buffer = std::shared_ptr<unsigned char[]>(new unsigned char[file_handle->size]);
        file.seekg(0, std::ios::beg);
        file.read((char *)file_handle->buffer.get(), file_handle->size);
        file.close();
    }
    return file_handle;
};
