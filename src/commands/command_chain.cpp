#include "commands/command_chain.h"

#include <iostream>

bool CommandChain::Execute() {
  if (this->current_command == nullptr) {
    return false;
  }
  bool result = this->current_command->Execute();
  auto current_ptr = this->next_command_chain;
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
    this->current_command = std::move(command);
    return;
  }
  auto current_command_chain = this;
  while (current_command_chain->next_command_chain != nullptr) {
    current_command_chain = current_command_chain->next_command_chain;
  }
  current_command_chain->next_command_chain = new CommandChain();
  current_command_chain->next_command_chain->current_command =
      std::move(command);
}