#include "states/base_state.h"

#include <cstring>

BaseState::BaseState(std::shared_ptr<libusb_device_handle *> device): device_(device) {}

BaseState::BaseState(std::shared_ptr<libusb_device_handle *> device, std::vector<unsigned char> valid_message_back)
    : device_(device), valid_message_back_(valid_message_back) {}

bool BaseState::IsMessageValid(std::vector<unsigned char> &message) const {
    return memcmp(this->valid_message_back_.data(), message.data(), this->valid_message_back_.size());
}

std::shared_ptr<libusb_device_handle *> BaseState::GetDevice() const {
    return device_;
}
