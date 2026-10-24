#ifndef RYUJINIII_DELETE_COMMAND_H
#define RYUJINIII_DELETE_COMMAND_H
#include "base_command.h"

/**
 * Command to delete a memory space
 */
class DeleteCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets the reference to wrapper
     * @param wrapper Reference to libusb wrapper
     */
    DeleteCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);

    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default delete instruction
     */
    const std::vector<unsigned char> kDelete = {0xec, 0x73, 0x03};
    /**
     * Default validation of response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x73};
};

#endif // RYUJINIII_DELETE_COMMAND_H
