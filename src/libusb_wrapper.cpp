#include "libusb_wrapper.h"
#include <cstring>
#include <iostream>

LibUsbWrapper::LibUsbWrapper() : LibUsbWrapperBase() {}

LibUsbWrapper::~LibUsbWrapper() {
    if (this->handle_ != nullptr) {
        libusb_close(*this->handle_.get());
    }
}

bool LibUsbWrapper::SendInterrupt(unsigned char endpoint, std::vector<unsigned char> &data) const {
    int transferred;
    if (int result = libusb_interrupt_transfer(*(this->handle_.get()), endpoint, data.data(),
                                               static_cast<int>(data.size()), &transferred, this->default_time_out_)) {
        std::cerr << "endpoint(" << std::hex << static_cast<int>(endpoint) << "): " << libusb_strerror(result)
                  << std::endl;
        return false;
    }
    return true;
}
void LibUsbWrapper::SetTimeout(int timeout) { this->default_time_out_ = timeout; }
void LibUsbWrapper::SetHandle(std::shared_ptr<libusb_device_handle *> handle) { this->handle_ = std::move(handle); }
bool LibUsbWrapper::InitializeDevice(int deviceId, int productId) {
    libusb_init(nullptr);
    this->SetHandle(std::make_shared<libusb_device_handle *>());
    libusb_device **dev_list = nullptr;
    ssize_t result_device_list = libusb_get_device_list(nullptr, &dev_list);
    for (int i = 0; i < result_device_list; i++) {
        std::shared_ptr<libusb_device_descriptor> desc = std::make_shared<libusb_device_descriptor>();
        libusb_get_device_descriptor(dev_list[i], desc.get());
        if (desc->idVendor == deviceId && desc->idProduct == productId) {
            libusb_open(dev_list[i], (this->handle_.get()));
            libusb_reset_device(*(this->handle_.get()));
            libusb_open(dev_list[i], (this->handle_.get()));
            libusb_set_auto_detach_kernel_driver(*(this->handle_.get()), 1);
            libusb_set_configuration(*(this->handle_.get()), 1);
            break;
        }
    }
    libusb_free_device_list(dev_list, 1);
    if (!this->handle_.get()) {
        return false;
    }
    return true;
}

bool LibUsbWrapper::ClaimInterfaces(int interface) const {
    return libusb_claim_interface(*(this->handle_.get()), interface) == 0;
}

bool LibUsbWrapper::HaltEndpoint(int endpoint) const {
    return libusb_clear_halt(*(this->handle_.get()), endpoint) == 0;
}

bool LibUsbWrapper::ReleaseInterface(int interface) const {
    return libusb_release_interface(*(this->handle_.get()), interface) == 0;
}

bool LibUsbWrapper::SendControl(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index,
                                std::vector<unsigned char> &buffer, uint16_t length) const {
    if (int result = libusb_control_transfer(*(this->handle_.get()), request_type, request, value, index, buffer.data(),
                                             length, this->default_time_out_);
        result < 0) {
        std::cerr << libusb_strerror(result) << std::endl;
        return false;
    }
    return true;
}

bool LibUsbWrapper::SendBulk(unsigned char endpoint, std::vector<unsigned char> &data) const {
    int transferred;
    if (int result = libusb_bulk_transfer(*(this->handle_.get()), endpoint, data.data(), static_cast<int>(data.size()),
                                          &transferred, this->default_time_out_)) {
        std::cerr << "endpoint(" << std::hex << static_cast<int>(endpoint) << "): " << libusb_strerror(result)
                  << std::endl;
        return false;
    }
    return true;
}
