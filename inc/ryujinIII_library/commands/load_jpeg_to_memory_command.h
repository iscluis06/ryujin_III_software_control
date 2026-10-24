#ifndef RYUJINIII_LOAD_JPEG_TO_MEMORY_COMMAND_H
#define RYUJINIII_LOAD_JPEG_TO_MEMORY_COMMAND_H
#include "base_command.h"

/**
 * Command that "loads" images to memory to be used by slideshow command.
 */
class LoadJPEGToMemoryCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Instance to LibUsbWrapperBase
     * @param index Index for memory slot to load
     * @param instruction Consecutive for the given memory space
     */
    LoadJPEGToMemoryCommand(std::shared_ptr<LibUsbWrapperBase> base, int index, int instruction);
    /**
     * Returns the class name for testing purposes
     * @return the name of the class
     */
    std::string GetClassName() const override;

private:
    /**
     * Default LoadJPEG command instruction
     */
    std::vector<unsigned char> kInstruction = {0xec, 0x60, 0x00, 0x01, 0x10, 0x00};
    /**
     * Index to memory slot
     */
    const int kMemorySlotIndex = 5;
    /**
     * Index for instruction consecutive
     */
    const int kInstructionIndex = 2;
};

#endif // RYUJINIII_LOAD_JPEG_TO_MEMORY_COMMAND_H
