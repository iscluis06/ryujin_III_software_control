#ifndef RYUJINIII_TURN_ON_COMMAND_H
#define RYUJINIII_TURN_ON_COMMAND_H

#include "base_command.h"

/**
 * Command to turn on the display
 */
class TurnOnCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets the wrapper property
     * @param wrapper Reference to libusb wrapper
     */
    TurnOnCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);

    ~TurnOnCommand() override = default;

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
