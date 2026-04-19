#ifndef RYUJINIII_LIBUSB_WRAPP_H
#define RYUJINIII_LIBUSB_WRAPP_H

#include <libusb-1.0/libusb.h>
#include <string>

class LibUsbWrapp {
public:
    static void SendInterruptAndPrintError(libusb_device_handle *dev_handle,
    unsigned char endpoint, unsigned char *data, int length,
    int *transferred, unsigned int timeout);
    static void SendBulkAndPrintError(libusb_device_handle *dev_handle,
    unsigned char endpoint, unsigned char *data, int length,
    int *transferred, unsigned int timeout);
};

#endif //RYUJINIII_LIBUSB_WRAPP_H
