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
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kSelectGif = {0xec, 0x51, 0x10, 0x01};
    /**
     * Default instruction to validate the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x51};
};

#endif // RYUJINIII_SELECT_GIF_COMMAND_H
