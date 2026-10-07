#ifndef RYUJINIII_START_JPEG_SELECTION_COMMAND_H
#define RYUJINIII_START_JPEG_SELECTION_COMMAND_H

#include "commands/base_command.h"
/**
 * Command that issues the start of a list of commands
 */
class StartInstructionCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     */
    StartInstructionCommand(std::shared_ptr<LibUsbWrapperBase> base);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default instruction command
     */
    std::vector<unsigned char> kInstruction = {0xec, 0xdc};
};

#endif // RYUJINIII_START_JPEG_SELECTION_COMMAND_H
