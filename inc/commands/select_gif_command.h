#ifndef RYUJINIII_SELECT_GIF_COMMAND_H
#define RYUJINIII_SELECT_GIF_COMMAND_H
#include "base_command.h"
/**
 * Command to upload a gif file
 */
class SelectGifCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets wrapper and memory index properties.
     * @param wrapper Reference to libusb wrapper
     * @param memory_index Memory space where to upload the gif
     */
    SelectGifCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index);
    /**
     * Default execution of command
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default command instruction
     */
    const unsigned char kSelectGif[4] = {0xec, 0x51, 0x10, 0x01};
    /**
     * Default instruction to validate the response
     */
    const unsigned char kValidateResponse[4] = {0xec, 0x51};
    /**
     * Memory index where to upload the gif file
     */
    int memory_index_;
};

#endif // RYUJINIII_SELECT_GIF_COMMAND_H
