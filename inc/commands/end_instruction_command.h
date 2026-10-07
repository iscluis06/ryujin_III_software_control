#ifndef RYUJINIII_END_JPEG_MODE_COMMAND_H
#define RYUJINIII_END_JPEG_MODE_COMMAND_H

#include "commands/base_command.h"
/**
 * Command to "notifies" the end of instructions (I suppose)
 */
class EndInstructionCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     */
    EndInstructionCommand(std::shared_ptr<LibUsbWrapperBase> base);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kInstruction = {0xec, 0x51, 0x1f};
};

#endif // RYUJINIII_END_JPEG_MODE_COMMAND_H
