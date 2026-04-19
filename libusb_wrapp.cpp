#include "inc/libusb_wrapp.h"
#include <iostream>
#include <thread>

void LibUsbWrapp::SendInterruptAndPrintError(libusb_device_handle *dev_handle,
                                             unsigned char endpoint, unsigned char *data, int length,
                                             int *transferred, unsigned int timeout) {
    int result = libusb_interrupt_transfer(dev_handle, endpoint, data, length, transferred, timeout);
    if (result) {
        std::cerr << libusb_strerror(result);
        exit(-1);
    }
}

void LibUsbWrapp::SendBulkAndPrintError(libusb_device_handle *dev_handle, unsigned char endpoint, unsigned char *data,
    int length, int *transferred, unsigned int timeout) {
    int result = libusb_bulk_transfer(dev_handle, endpoint, data, length, transferred, timeout);
    if (result) {
        std::cerr << libusb_strerror(result);
    }
}
