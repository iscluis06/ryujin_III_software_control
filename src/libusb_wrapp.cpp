#include "libusb_wrapp.h"
#include <iostream>
#include <cstring>

LibUsbWrapp::LibUsbWrapp(std::shared_ptr<libusb_device_handle *> handle, int default_time_out) : handle_(handle),
    default_time_out_(default_time_out) {
}

bool LibUsbWrapp::SendInterrupt(unsigned char endpoint, std::vector<unsigned char> &data) const {
    int transferred;
    if (int result = libusb_interrupt_transfer(*(this->handle_.get()), endpoint, data.data(),
                                               static_cast<int>(data.size()), &transferred, this->default_time_out_)) {
        std::cerr << "endpoint(" << std::hex << static_cast<int>(endpoint) << "): " << libusb_strerror(result) <<
                std::endl;
        return false;
    }
    return true;
}

bool LibUsbWrapp::SendControl(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index,
                              std::vector<unsigned char> &buffer, uint16_t length) const {
    if (int result = libusb_control_transfer(*(this->handle_.get()), request_type, request, value, index, buffer.data(),
                                             length, this->default_time_out_); result < 0) {
        std::cerr << libusb_strerror(result) << std::endl;
        return false;
    }
    return true;
}

bool LibUsbWrapp::SendBulk(unsigned char endpoint, std::vector<unsigned char> &data) const {
    int transferred;
    if (int result = libusb_bulk_transfer(*(this->handle_.get()), endpoint, data.data(), static_cast<int>(data.size()),
                                          &transferred, this->default_time_out_)) {
        std::cerr << "endpoint(" << std::hex << static_cast<int>(endpoint) << "): " << libusb_strerror(result) <<
                std::endl;
        return false;
    }
    return true;
}

std::vector<unsigned char> LibUsbWrapp::FillArray(const unsigned char *array, int array_size, int desired_size) {
    std::vector<unsigned char> buffer(desired_size, 0);
    memcpy(buffer.data(), array, array_size);
    return buffer;
}
