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
        libusb_clear_halt(*(this->device.get()), this->kVendorDeviceOut);
        libusb_clear_halt(*(this->device.get()), this->kHidDeviceOut);
        libusb_clear_halt(*(this->device.get()), this->kVendorDeviceIn);
        libusb_clear_halt(*(this->device.get()), this->kHidDeviceIn);
        std::vector<unsigned char> buffer = std::vector<unsigned char>(255);
        // this->lusb_->SendControl(0x80, 8, 0x0000, 0, buffer, 1);
        // this->lusb_->SendControl(0x80, 6, 0x0300, 0x0409, buffer, 4);
        // this->lusb_->SendControl(0x80, 6, 0x0302, 0x0409, buffer, 255);
        // this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 8);
        // this->lusb_->SendControl(0x80, 6, 0x0200, 0x0000, buffer, 9);
        // this->lusb_->SendControl(0x80, 6, 0x0200, 0x0000, buffer, 64);
        // this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 18);
        // this->lusb_->SendControl(0x80, 6, 0x0200, 0x0000, buffer, 64);
        // this->lusb_->SendControl(0x80, 6, 0x0303, 0x0409, buffer, 255);
        // this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 64);
        // this->lusb_->SendControl(0x80, 6, 0x0100, 0x0000, buffer, 18);
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

void RyujinDevice::Reset() const{
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

void RyujinDevice::TurnOnLedDisplay() const{
    auto buffer = RyujinDevice::FillArray(this->kTurnOn, 3, this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
};

void RyujinDevice::TurnOffLedDisplay() const{
    auto buffer = RyujinDevice::FillArray(this->kTurnOff, 2, this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
}

void RyujinDevice::SelectGifFromMemory(int memory_index) const{
    std::vector<unsigned char> buffer = FillArray(this->kSelectGif, sizeof(this->kSelectGif), this->kDefaultInterruptDataLength);
    buffer[4] = memory_index;
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
}

void RyujinDevice::DeleteFromMemory(int memory_index) const{
    this->SelectGifFromMemory(memory_index);
    std::vector<unsigned char> buffer = FillArray(this->kDelete, sizeof(this->kDelete), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
}

void RyujinDevice::UploadGif(const std::string &path, short memory_space) {
    std::vector<unsigned char> buffer_response = RyujinDevice::FillArray(nullptr, 0, this->kDefaultInterruptDataLength);
    std::vector<unsigned char> buffer = RyujinDevice::FillArray(this->kTransaction, sizeof(this->kTransaction), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    this->lusb_->SendInterrupt(this->kHidDeviceIn, buffer_response);
    //valid repsonse back
    unsigned char valid_transaction[] = {0xec, 0x71, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    if ( memcmp(buffer_response.data(), valid_transaction, sizeof(valid_transaction)) != 0) {
        std::cerr << "Invalid transaction from device, exiting..." << std::endl;
        exit(-1);
    }

    buffer = RyujinDevice::FillArray(this->kStartTransaction, sizeof(this->kStartTransaction), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    this->lusb_->SendInterrupt(this->kHidDeviceIn, buffer_response);
    //valid message back
    unsigned char valid_start_transaction[] = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
    if ( memcmp(buffer_response.data(), valid_start_transaction, sizeof(valid_start_transaction)) != 0) {
        std::cerr << "Invalid transaction start from device, exiting..." << std::endl;
        exit(-1);
    }

    buffer = RyujinDevice::FillArray(this->kSelectMemory, sizeof(this->kSelectMemory), this->kDefaultInterruptDataLength);
    buffer[4] = memory_space;
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    this->lusb_->SendInterrupt(this->kHidDeviceIn, buffer_response);
    //valid message back
    unsigned char valid_select_memory[] = {0xec, 0x72, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    if ( memcmp(buffer_response.data(), valid_select_memory, sizeof(valid_select_memory)) != 0) {
        std::cerr << "Invalid select memory from device, exiting..." << std::endl;
        exit(-1);
    }

    buffer = RyujinDevice::FillArray(this->kStartUpload, sizeof(this->kStartUpload), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    this->lusb_->SendInterrupt(this->kHidDeviceIn, buffer_response);
    //valid message back
    unsigned char valid_start_upload[] = {0xec, 0x73, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    if ( memcmp(buffer_response.data(), valid_start_upload, sizeof(valid_start_upload)) != 0) {
        std::cerr << "Invalid start upload from device, exiting..." << std::endl;
        exit(-1);
    }

    std::shared_ptr<RyujinDevice::FileHandle> file_handle = RyujinDevice::ReadFile(path);
    int iterations = std::ceil(file_handle->size/kDefaultBulkLength);
    std::array<unsigned char,3> size_array = GetSizeToHex(file_handle->size);
    buffer = RyujinDevice::FillArray(this->kReportedSize, sizeof(this->kReportedSize), this->kDefaultInterruptDataLength);
    memcpy(buffer.data()+3, size_array.data(), sizeof(unsigned char)*3);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    this->lusb_->SendInterrupt(this->kHidDeviceIn, buffer_response);
    //valid message back
    unsigned char valid_reported_size[] = {0xec, 0x7f, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    if ( memcmp(buffer_response.data(), valid_reported_size, sizeof(valid_reported_size)) != 0) {
        std::cerr << "Invalid reported size from device, exiting..." << std::endl;
        exit(-1);
    }

    buffer.reserve(this->kDefaultBulkLength);
    buffer.resize(this->kDefaultBulkLength);
    libusb_clear_halt(*(this->device.get()), this->kHidDeviceIn);
    for (int i=0; i<iterations; i++) {
        std::cout << "upload porcentage: " << 100*((float)(i+1)/(float)iterations) <<"%" << '\r';
        std::cout.flush();
        memset(buffer.data(), 0, sizeof(unsigned char)*this->kDefaultBulkLength);
        memcpy(buffer.data(),file_handle->buffer.get()+(i*this->kDefaultBulkLength),sizeof(unsigned char)*this->kDefaultBulkLength);
        this->lusb_->SendBulk(this->kVendorDeviceOut, buffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        this->lusb_->SendInterrupt(this->kHidDeviceIn, buffer_response);
        //valid message back
        //unsigned char bytes[] = {0xee, 0x14, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    }

    buffer = RyujinDevice::FillArray(this->kEndUpload, sizeof(this->kEndUpload), this->kDefaultInterruptDataLength);
    this->lusb_->SendInterrupt(this->kHidDeviceOut, buffer);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    this->lusb_->SendInterrupt(this->kHidDeviceIn, buffer_response);
};

std::vector<unsigned char> RyujinDevice::FillArray(const unsigned char *array, int array_size, int desired_size) {
    std::vector<unsigned char> buffer(desired_size, 0);
    memcpy(buffer.data(), array, array_size);
    return buffer;
}

std::array<unsigned char, 3> RyujinDevice::GetSizeToHex(int size) {
    std::array<unsigned char, 3> array_size = {0};
    int i = 0;
    int value = size;
    while (true) {
        int hex_val = value%16;
        if (i%2 == 0) {
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

std::shared_ptr<RyujinDevice::FileHandle> RyujinDevice::ReadFile(const std::string &path) {
    std::ifstream file(path, std::ios::in|std::ios::binary|std::ios::ate);
    std::shared_ptr<RyujinDevice::FileHandle> file_handle = std::make_shared<RyujinDevice::FileHandle>();
    if ( file.is_open()) {
        file_handle->size = file.tellg();
        file_handle->buffer = std::shared_ptr<unsigned char[]>(new unsigned char[file_handle->size]);
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char *>(file_handle->buffer.get()), file_handle->size);
        file.close();
    }
    return file_handle;
};
