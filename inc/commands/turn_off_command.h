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
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default instruction command
     */
    const std::vector<unsigned char> kTurnOff = {0xec, 0x51};
};

#endif // RYUJINIII_TURN_OFF_COMMAND_H
