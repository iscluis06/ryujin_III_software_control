#ifndef RYUJINIII_SLIDE_SHOW_JPEG_MODE_COMMAND_H
#define RYUJINIII_SLIDE_SHOW_JPEG_MODE_COMMAND_H

#include "commands/base_command.h"

/**
 * Command to start jpeg mode for slideshow
 */
class SlideShowJpegModeCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     */
    SlideShowJpegModeCommand(std::shared_ptr<LibUsbWrapperBase> base);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    std::vector<unsigned char> kInstruction = {0xec, 0x60, 0x3, 0x1, 0x10, 0x2};
};

#endif // RYUJINIII_SLIDE_SHOW_JPEG_MODE_COMMAND_H
