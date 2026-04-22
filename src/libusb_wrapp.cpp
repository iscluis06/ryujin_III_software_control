#include "libusb_wrapp.h"
#include <iostream>

LibUsbWrapp::LibUsbWrapp(std::shared_ptr<libusb_device_handle *> handle, int default_time_out):
 handle_(handle), default_time_out_(default_time_out){}
void LibUsbWrapp::SendInterrupt(unsigned char endpoint,std::vector<unsigned char>data) const {
    int transferred;
    if (int result = libusb_interrupt_transfer(*(this->handle_.get()), endpoint, data.data(), data.size(), &transferred, this->default_time_out_)) {
        std::cerr << libusb_strerror(result);
        exit(-1);
    }
}
void LibUsbWrapp::SendControl(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index, std::vector<unsigned char> buffer, uint16_t length) const {
    if (int result = libusb_control_transfer(*(this->handle_.get()), request_type, request, value, index, buffer.data(), length, this->default_time_out_); result < 0) {
        std::cerr << libusb_strerror(result);
        exit(-1);
    }
}

void LibUsbWrapp::SendBulk(unsigned char endpoint,std::vector<unsigned char>data) const {
    int transferred;
    if (int result = libusb_bulk_transfer(*(this->handle_.get()), endpoint, data.data(), data.size(), &transferred, this->default_time_out_)) {
        std::cerr << libusb_strerror(result);
        exit(-1);
    }
}