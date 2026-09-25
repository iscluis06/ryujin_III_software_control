#ifndef RYUJINIII_SELECT_JPEG_COMMAND_H
#define RYUJINIII_SELECT_JPEG_COMMAND_H
#include "base_command.h"
/**
 * Command to upload a gif file
 */
class SelectJpegCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets wrapper and memory index properties.
     * @param wrapper Reference to libusb wrapper
     * @param memory_index Memory space where to upload the gif
     */
    SelectJpegCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kSelectJpeg = {0xec, 0x60, 0x0, 0x1, 0x10, 0x8}; // Last space is memory slot
    const int kJpegIndex = 5;
};

#endif // RYUJINIII_SELECT_JPEG_COMMAND_H
