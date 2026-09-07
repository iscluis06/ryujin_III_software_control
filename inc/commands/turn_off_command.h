#ifndef RYUJINIII_TURN_OFF_COMMAND_H
#define RYUJINIII_TURN_OFF_COMMAND_H
#include "base_command.h"

/**
 * Command to turn off the display
 */
class TurnOffCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets the wrapper property
     * @param wrapper Reference to libusb wrapper
     */
    TurnOffCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);
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
