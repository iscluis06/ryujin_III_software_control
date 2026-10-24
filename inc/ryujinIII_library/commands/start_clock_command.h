#ifndef RYUJINIII_START_CLOCK_COMMAND_H
#define RYUJINIII_START_CLOCK_COMMAND_H

#include "commands/base_command.h"

/**
 * Start clock command
 */
class StartClockCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     */
    StartClockCommand(std::shared_ptr<LibUsbWrapperBase> base);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    std::vector<unsigned char> kInstruction = {0xec, 0x51, 0x8, 0x0, 0x1};
};


#endif // RYUJINIII_START_CLOCK_COMMAND_H
