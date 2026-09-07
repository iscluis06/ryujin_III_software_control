#ifndef RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
#define RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
#include "base_command.h"
/**
 * Command to select the memory space
 */
class SelectMemorySpaceCommand : public BaseCommand {
public:
    /**
     * Constructor which sets wrapper and memory index properties
     * @param wrapper Reference to libusb wrapper
     * @param memory_index Memory space to select from device
     */
    SelectMemorySpaceCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index);

    /**
     * Default execution of command
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Memory index to select from device
     */
    int memory_index_;
    /**
     * Default instruction command
     */
    const unsigned char kSelectMemory[4] = {0xec, 0x72, 0x01, 0x02};
    /**
     * Default instruction to validate the response
     */
    const unsigned char kValidateResponse[2] = {0xec, 0x72};
};

#endif // RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
