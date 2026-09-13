#include "commands/base_command.h"

#include <cstring>
#include <iostream>
#include <thread>

BaseCommand::BaseCommand(std::shared_ptr<LibUsbWrapperBase> wrapper) : wrapper_(std::move(wrapper)) {}

bool BaseCommand::IsMessageValid(const std::vector<unsigned char> &message) const {
    if (memcmp(this->validation_message_.data(), message.data(), this->validation_message_.size()) != 0) {
        std::cout << "Response back was invalid - " << this->GetClassName() << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<LibUsbWrapperBase> BaseCommand::GetWrapper() const { return this->wrapper_; }
std::string BaseCommand::GetClassName() const { return "BaseCommand"; }
void BaseCommand::SetInstruction(std::vector<unsigned char> instruction) {
    this->instruction_ = std::move(instruction);
}
void BaseCommand::SetTimeout(int timeout) { this->timeout_ = timeout; }
void BaseCommand::SetValidationMessage(std::vector<unsigned char> validation_message) {
    this->validation_message_ = std::move(validation_message);
}
std::vector<unsigned char> BaseCommand::GetMessageBack() { return this->message_back_; }
void BaseCommand::SetCallBackFunction(std::function<void()> function_pointer) { this->callback_ = function_pointer; }
bool BaseCommand::Execute() {
    if (!this->GetWrapper()->SendInterrupt(this->endpoint_out_, this->instruction_)) {
        std::cerr << "Failed to execute instruction" << std::endl;
        return false;
    }
    if (this->read_back_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(this->timeout_));
        this->message_back_ = std::vector<unsigned char>(this->response_back_size_, 0);
        if (!this->GetWrapper()->SendInterrupt(this->endpoint_in_, this->message_back_)) {
            std::cerr << "Failed to read from input endpoint" << std::endl;
            return false;
        }
    }
    if (callback_) {
        callback_();
    }
    if (!this->validation_message_.empty()) {
        return this->IsMessageValid(this->message_back_);
    }
    return true;
}
void BaseCommand::ShouldReadBack(bool read_back) { this->read_back_ = read_back; }
void BaseCommand::SetEndpointOut(int endpoint_out) { this->endpoint_out_ = endpoint_out; }
void BaseCommand::SetEndpointIn(int endpoint_in) { this->endpoint_in_ = endpoint_in; }
void BaseCommand::SetResponseBackSize(int size) { this->response_back_size_ = size; }
