#ifndef RYUJINIII_TRANSACTION_COMMAND_H
#define RYUJINIII_TRANSACTION_COMMAND_H

#include "base_command.h"
#include <libusb-1.0/libusb.h>
#include <memory>

/**
 * Command start a transaction
 */
class TransactionCommand : public BaseCommand {
public:
  /**
   * Constructor which sets the device property
   * @param device Reference to device handler
   */
  TransactionCommand(std::shared_ptr<libusb_device_handle *> device);

  /**
   * Default execution command
   * @return True on success, otherwise false
   */
  bool Execute() override;

private:
  /**
   * Default command instruction
   */
  const unsigned char kTransaction[4] = {0xec, 0x71, 0x01, 0x01};
  /**
   * Default instruction to validate the response
   */
  const unsigned char kValidateResponse[2] = {0xec, 0x71};
};

#endif // RYUJINIII_TRANSACTION_COMMAND_H
