#ifndef RYUJINIII_LIBUSB_WRAPP_H
#define RYUJINIII_LIBUSB_WRAPP_H

#include <libusb-1.0/libusb.h>
#include <vector>
#include <memory>

class LibUsbWrapp {
public:
    LibUsbWrapp(std::shared_ptr<libusb_device_handle *> handle, int default_time_out);
    void SendInterrupt(unsigned char endpoint,std::vector<unsigned char>data) const;
    void SendControl(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index, std::vector<unsigned char> buffer, uint16_t length) const;
    void SendBulk(unsigned char endpoint,std::vector<unsigned char>data) const;
private:
    std::shared_ptr<libusb_device_handle *> handle_;
    int default_time_out_;
};

#endif //RYUJINIII_LIBUSB_WRAPP_H
