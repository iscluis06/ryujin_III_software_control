#ifndef RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
#define RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
#include "base_command.h"
/**
 * Command to select the memory space
 */
class SelectMemorySpaceJPEGCommand : public BaseCommand {
public:
    /**
     * Constructor which sets wrapper and memory index properties
     * @param wrapper Reference to libusb wrapper
     * @param memory_index Memory space to select from device
     */
    SelectMemorySpaceJPEGCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index);

    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default instruction command
     */
    const std::vector<unsigned char> kSelectMemory = {0xec, 0x72, 0x01, 0x01};
    /**
     * Default instruction to validate the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x72};
    const int kJpegIndex = 4;
};

#endif // RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
