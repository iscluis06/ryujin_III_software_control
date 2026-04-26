#ifndef RYUJINIII_BASE_STATE_H
#define RYUJINIII_BASE_STATE_H

#include <memory>
#include <libusb-1.0/libusb.h>
#include <vector>

class BaseState {
public:
    BaseState(std::shared_ptr<libusb_device_handle *> device);
    BaseState(std::shared_ptr<libusb_device_handle *> device, std::vector<unsigned char> valid_message_back);
    virtual ~BaseState() = default;
    virtual bool Execute(unsigned char endpoint, std::vector<unsigned char> &message) = 0;
    bool IsMessageValid(std::vector<unsigned char> &message) const;
    std::shared_ptr<libusb_device_handle *> GetDevice() const;
    const int kTimeout = 1000;
private:
    std::shared_ptr<libusb_device_handle *> device_;
    std::vector<unsigned char> valid_message_back_;
};

#endif //RYUJINIII_BASE_STATE_H
