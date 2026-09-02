#ifndef RYUJINIII_DELETE_COMMAND_H
#define RYUJINIII_DELETE_COMMAND_H
#include "base_command.h"

/**
 * Command to delete a memory space
 */
class DeleteCommand : public BaseCommand {
public:
  /**
   * Constructor which also sets the device handler property
   * @param device Reference to device handler
   */
  DeleteCommand(std::shared_ptr<libusb_device_handle *> device);

  /**
   * Default execution of command
   * @return True on succeed, otherwise false
   */
  bool Execute() override;

private:
  /**
   * Default delete instruction
   */
  const unsigned char kDelete[3] = {0xec, 0x73, 0x03};
  /**
   * Default validation of response
   */
  const unsigned char kValidateResponse[2] = {0xec, 0x73};
};

#endif // RYUJINIII_DELETE_COMMAND_H
