#include "commands/command_chain.h"

CommandChain::~CommandChain() {
    if (this->current_command == nullptr) {
        return;
    }
    delete this->current_command;
    auto current_ptr = this->next_command_chain;
    while (current_ptr != nullptr && current_ptr->current_command != nullptr) {
        delete current_ptr->current_command;
        current_ptr = current_ptr->next_command_chain;
    }
}

bool CommandChain::Execute() {
    if (this->current_command == nullptr) {
        return false;
    }
    bool result = false;
    auto current_ptr = this;
    while (current_ptr != nullptr && current_ptr->current_command != nullptr) {
        result = current_ptr->current_command->Execute();
        current_ptr = current_ptr->next_command_chain;
        if (result == false) {
            return false;
        }
    }
    return result;
}

void CommandChain::AddCommand(BaseCommand *command) {
    if (this->current_command == nullptr) {
        this->current_command = command;
        return;
    }
    auto current_command_chain = this;
    while (current_command_chain->next_command_chain != nullptr) {
        current_command_chain = current_command_chain->next_command_chain;
    }
    current_command_chain->next_command_chain = new CommandChain();
    current_command_chain->next_command_chain->current_command = command;
}
