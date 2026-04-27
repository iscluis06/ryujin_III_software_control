#include "states/base_state.h"

#include <cstring>
#include <iostream>

BaseState::BaseState(std::shared_ptr<libusb_device_handle *> device) : device_(device) {
}

BaseState::BaseState(std::shared_ptr<libusb_device_handle *> device,
                     const unsigned char *valid_message_back,
                     int valid_message_back_size)
    : device_(device), valid_message_back_(valid_message_back), valid_message_back_size_(valid_message_back_size) {
}

bool BaseState::IsMessageValid(const std::vector<unsigned char> &message) const {
    if (memcmp(this->valid_message_back_, message.data(), this->valid_message_back_size_) != 0) {
        std::cerr << "Response back was invalid " << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<libusb_device_handle *> BaseState::GetDevice() const {
    return device_;
}
