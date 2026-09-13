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

    /**
     * Default constructor
     */
    ~TurnOnCommand() override = default;
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default instruction command
     */
    const std::vector<unsigned char> kTurnOn = {0xec, 0x51, 0x14};
};

#endif // RYUJINIII_TURN_ON_COMMAND_H
