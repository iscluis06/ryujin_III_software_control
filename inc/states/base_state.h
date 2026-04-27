#ifndef RYUJINIII_BASE_STATE_H
#define RYUJINIII_BASE_STATE_H

#include <memory>
#include <libusb-1.0/libusb.h>
#include <vector>

class BaseState {
public:
    BaseState(std::shared_ptr<libusb_device_handle *> device);

    BaseState(std::shared_ptr<libusb_device_handle *> device,
              const unsigned char *valid_message_back,
              int valid_message_back_size);

    virtual ~BaseState() = default;

    virtual bool Execute() = 0;

    bool IsMessageValid(const std::vector<unsigned char> &message) const;

    std::shared_ptr<libusb_device_handle *> GetDevice() const;

    const int kTimeout = 1000;

private:
    std::shared_ptr<libusb_device_handle *> device_;
    const unsigned char *valid_message_back_ = nullptr;
    int valid_message_back_size_ = 0;
};

#endif //RYUJINIII_BASE_STATE_H
