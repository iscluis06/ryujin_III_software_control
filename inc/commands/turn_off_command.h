#ifndef RYUJINIII_TURN_OFF_COMMAND_H
#define RYUJINIII_TURN_OFF_COMMAND_H
#include "base_command.h"

/**
 * Command to turn off the display
 */
class TurnOffCommand : BaseCommand {
public:
  /**
   * Constructor which also sets the device property
   * @param device Reference to device handler
   */
  TurnOffCommand(std::shared_ptr<libusb_device_handle *> device);
  /**
   * Default command execution
   * @return True on success, otherwise false
   */
  bool Execute() override;

private:
  /**
   * Default instruction command
   */
  const unsigned char kTurnOff[2] = {0xec, 0x51};
};

#endif // RYUJINIII_TURN_OFF_COMMAND_H
