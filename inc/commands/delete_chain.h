#ifndef RYUJINIII_DELETE_CHAIN_H
#define RYUJINIII_DELETE_CHAIN_H
#include "command_chain.h"
#include <libusb-1.0/libusb.h>
#include <memory>

/**
 * Command chain to delete a gif from memory (1-10)
 */
class DeleteChain : public CommandChain {
public:
  /**
   * Deletes a gif from device memory
   * @param device Reference to device handler
   * @param memory_index Memory index to delete
   */
  DeleteChain(std::shared_ptr<libusb_device_handle *> device, int memory_index);

  /**
   * Execution of chain commands
   * @return True on success, otherwise false
   */
  bool Execute() override;

private:
  /**
   * Default number of tries before canceling command retries
   */
  const int kMaxTries_ = 3;
};

#endif // RYUJINIII_DELETE_CHAIN_H
