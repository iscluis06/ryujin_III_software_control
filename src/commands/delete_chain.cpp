#include "commands/delete_chain.h"

#include "commands/default_gif.h"
#include "commands/delete_command.h"
#include "commands/select_memory_space_command.h"

DeleteChain::DeleteChain(std::shared_ptr<libusb_device_handle *> device,
                         int memory_index)
    : CommandChain() {
  this->AddCommand(new DefaultGif(device));
  this->AddCommand(new SelectMemorySpaceCommand(device, memory_index));
  this->AddCommand(new DeleteCommand(device));
}

bool DeleteChain::Execute() {
  int no_retries = 0;
  while (no_retries < this->kMaxTries_) {
    if (this->CommandChain::Execute()) {
      return true;
    }
    no_retries++;
  }
  return false;
}
