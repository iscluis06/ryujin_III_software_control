#include "inc/ryujin_device.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <thread>

#include "inc/libusb_wrapp.h"

RyujinDevice::RyujinDevice() {
    libusb_init(nullptr);
    this->GetDevice();
    if (this->device) {
        libusb_set_auto_detach_kernel_driver(this->device, 1);
        libusb_set_configuration(this->device, 1);
        libusb_claim_interface(this->device, 0);
        libusb_claim_interface(this->device, 1);
        libusb_reset_device(device);
        unsigned char * buffer = new unsigned char[255];
        libusb_control_transfer(device, 0x80, 8, 0x0000, 0, buffer, 1, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0300, 0x0409, buffer, 4, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0302, 0x0409, buffer, 255, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0100, 0x0000, buffer, 8, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0200, 0x0000, buffer, 9, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0200, 0x0000, buffer, 64, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0100, 0x0000, buffer, 18, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0200, 0x0000, buffer, 64, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0303, 0x0409, buffer, 255, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0100, 0x0000, buffer, 64, 0);
        libusb_control_transfer(device, 0x80, 6, 0x0100, 0x0000, buffer, 18, 0);
        libusb_control_transfer(device, 0x21, 0x0a, 0x0000, 1, buffer, 0, 0);
        unsigned char bytes[] = {0xec, 0xdc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        libusb_interrupt_transfer(device, 0x02, bytes, sizeof(bytes), nullptr, 5000);
        libusb_interrupt_transfer(device, 0x82, buffer, 65, nullptr, 5000);
    }
}

RyujinDevice::~RyujinDevice() {
    if (device != nullptr) {
        libusb_release_interface(device, this->kConfigInterface);
        libusb_release_interface(device, this->kLedInterface);
        libusb_close(device);
    }
}

void RyujinDevice::Reset() {
    libusb_reset_device(this->device);
}

void RyujinDevice::GetDevice() {
    libusb_device **dev_list = nullptr;
    int result_device_list = libusb_get_device_list(nullptr, &dev_list);
    for (int i = 0; i < result_device_list; i++) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev_list[i], &desc);
        if (desc.idVendor == this->kAsusDeviceId && desc.idProduct == this->kRyujinProductId) {
            libusb_open(dev_list[i], &this->device);
            break;
        }
    }
}

bool RyujinDevice::IsDeviceAvailable() {
    return this->device != nullptr;
};

void RyujinDevice::TurnOnLedDisplay() {
    LibUsbWrapp::SendInterruptAndPrintError(this->device, this->kHidDeviceOut,
                                            this->FillArray(this->kTurnOn, 3, this->kDefaultInterruptDataLength),
                                            this->kDefaultInterruptDataLength,
                                            nullptr,
                                            this->kDefaultTimeOut);
};

void RyujinDevice::TurnOffLedDisplay() {
    LibUsbWrapp::SendInterruptAndPrintError(this->device, this->kHidDeviceOut,
                                            this->FillArray(this->kTurnOff, 2, this->kDefaultInterruptDataLength),
                                            this->kDefaultInterruptDataLength,
                                            nullptr,
                                            this->kDefaultTimeOut);
}

void RyujinDevice::SelectGifFromMemory(int memory_index) {
    unsigned char *buffer = FillArray(this->kSelectGif, sizeof(this->kSelectGif), this->kDefaultInterruptDataLength);
    buffer[4] = memory_index;
    LibUsbWrapp::SendInterruptAndPrintError(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength,
                                            nullptr, this->kDefaultTimeOut);
}

void RyujinDevice::DeleteFromMemory(int memory_index) {
    this->SelectGifFromMemory(memory_index);
    unsigned char *buffer = FillArray(this->kDelete, sizeof(this->kDelete), this->kDefaultInterruptDataLength);
    LibUsbWrapp::SendInterruptAndPrintError(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength,
                                            nullptr, this->kDefaultTimeOut);
}

void RyujinDevice::UploadGif(std::string path) {
    unsigned char * buffer_response = new unsigned char[65];
    int transfered;
    memset(buffer_response,0, this->kDefaultInterruptDataLength);
    unsigned char * buffer = new unsigned char[65];
    buffer = this->FillArray(this->kTransaction, sizeof(this->kTransaction), this->kDefaultInterruptDataLength);
    libusb_interrupt_transfer(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength,
        nullptr, this->kDefaultTimeOut);
    libusb_interrupt_transfer(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength,
        nullptr, this->kDefaultTimeOut);
    buffer = this->FillArray(this->kStartTransaction, sizeof(this->kStartTransaction), this->kDefaultInterruptDataLength);
    libusb_interrupt_transfer(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength,
        nullptr, this->kDefaultTimeOut);
    memset(buffer_response,0, this->kDefaultInterruptDataLength);
    libusb_interrupt_transfer(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength,
        nullptr, this->kDefaultTimeOut);
    buffer = this->FillArray(this->kSelectMemory, sizeof(this->kSelectMemory), this->kDefaultInterruptDataLength);
    buffer[4] = 0x02;
    libusb_interrupt_transfer(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength,
        nullptr, this->kDefaultTimeOut);
    memset(buffer_response,0, this->kDefaultInterruptDataLength);
    // libusb_interrupt_transfer(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength,
        // nullptr, this->kDefaultTimeOut);
    buffer = this->FillArray(this->kStartUpload, sizeof(this->kStartUpload), this->kDefaultInterruptDataLength);
    libusb_interrupt_transfer(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength, nullptr, this->kDefaultTimeOut);
    libusb_interrupt_transfer(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength, nullptr, this->kDefaultTimeOut);
    std::shared_ptr<RyujinDevice::FileHandle> file_handle = this->ReadFile(path);
    int iterations = std::ceil(file_handle->size/4096.0f);
    // std::array<unsigned char,3> size_array = GetSizeToHex(file_handle->size);
    // std::array<unsigned char,3> size_array = GetSizeToHex(iterations*4096);
    // buffer = this->FillArray(this->kReportedSize, sizeof(this->kReportedSize), this->kDefaultInterruptDataLength);
    // memcpy(buffer+3, size_array.data(), sizeof(unsigned char)*3);
    const unsigned char fixed_size_test[6] = {0xec, 0x7f, 0x02, 0x04, 0x19, 0x21};
    buffer = this->FillArray(fixed_size_test, sizeof(fixed_size_test), this->kDefaultInterruptDataLength);
    libusb_interrupt_transfer(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength, nullptr, this->kDefaultTimeOut);

    libusb_interrupt_transfer(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength,
            nullptr, this->kDefaultTimeOut);

    for (int i=0; i<iterations; i++) {
        int transfered;
        buffer = new unsigned char[4096];
        memset(buffer, 0, 4096);
        memcpy(buffer,file_handle->buffer.get()+(i*4096),4096);
        libusb_bulk_transfer(this->device, this->kVendorDeviceOut,
        buffer, 4096
        , &transfered, 5000);
        delete buffer;
        memset(buffer_response,0, this->kDefaultInterruptDataLength);
        libusb_interrupt_transfer(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength,
            nullptr, 0);
    }
    buffer = this->FillArray(this->kEndUpload, sizeof(this->kEndUpload), this->kDefaultInterruptDataLength);
    LibUsbWrapp::SendInterruptAndPrintError(this->device, this->kHidDeviceOut, buffer, this->kDefaultInterruptDataLength, nullptr, this->kDefaultTimeOut);
    memset(buffer_response,0, this->kDefaultInterruptDataLength);
    LibUsbWrapp::SendInterruptAndPrintError(this->device, 0x82, buffer_response, this->kDefaultInterruptDataLength,
        nullptr, this->kDefaultTimeOut);
    this->SelectGifFromMemory(0x02);

};

unsigned char *RyujinDevice::FillArray(const unsigned char *array, int array_size, int desired_size) {
    unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char) * desired_size);
    memset(buffer, 0, desired_size);
    memcpy(buffer, array, array_size);
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
