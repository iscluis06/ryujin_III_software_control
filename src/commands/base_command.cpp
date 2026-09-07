#include "commands/base_command.h"

#include <cstring>
#include <iostream>

BaseCommand::BaseCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : wrapper_(std::move(wrapper)) {}

BaseCommand::BaseCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, const unsigned char *valid_message_back,
                         int valid_message_back_size) :
    wrapper_(std::move(wrapper)), valid_message_back_(valid_message_back),
    valid_message_back_size_(valid_message_back_size) {}

bool BaseCommand::IsMessageValid(const std::vector<unsigned char> &message) const {
    if (memcmp(this->valid_message_back_, message.data(), this->valid_message_back_size_) != 0) {
        std::cout << "Response back was invalid " << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<LibUsbWrapperBase> BaseCommand::GetWrapper() const { return this->wrapper_; }
