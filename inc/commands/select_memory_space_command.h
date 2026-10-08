#ifndef RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
#define RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
#include "base_command.h"
/**
 * Command to select the memory space
 */
class SelectMemorySpaceCommand : public BaseCommand {
public:
    enum class MemoryType { JPEG = 1, GIF = 2 };
    /**
     * Constructor which sets wrapper and memory index properties
     * @param wrapper Reference to libusb wrapper
     * @param memory_index Memory space to select from device
     * @param type Type of memory slot, by default GIF
     */
    SelectMemorySpaceCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index,
                             MemoryType type = MemoryType::GIF);

    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default instruction command
     */
    const std::vector<unsigned char> kSelectMemory = {0xec, 0x72, 0x01, 0x02};
    /**
     * Default instruction to validate the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x72};
    const int kMemoryTypeIndex = 3;
};

#endif // RYUJINIII_SELECT_MEMORY_SPACE_COMMAND_H
