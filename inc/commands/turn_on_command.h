#ifndef RYUJINIII_TURN_ON_COMMAND_H
#define RYUJINIII_TURN_ON_COMMAND_H

#include "base_command.h"

/**
 * Command to turn on the display
 */
class TurnOnCommand : BaseCommand {
public:
  /**
   * Constructor which also sets the device property
   * @param device Reference to device handler
   */
  TurnOnCommand(std::shared_ptr<libusb_device_handle *> device);

  /**
   * Default execution command
   * @return True on success, otherwise false
   */
  bool Execute() override;

private:
  /**
   * Default instruction command
   */
  const unsigned char kTurnOn[3] = {0xec, 0x51, 0x14};
};

#endif // RYUJINIII_TURN_ON_COMMAND_H
