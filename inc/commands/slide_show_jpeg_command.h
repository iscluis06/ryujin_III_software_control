#ifndef RYUJINIII_SLIDESHOW_JPEG_COMMAND_H
#define RYUJINIII_SLIDESHOW_JPEG_COMMAND_H

#include "commands/base_command.h"

/**
 * Slide show command (jpegs)
 */
class SlideShowJpegCommand : public BaseCommand {
public:
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     * @param indexes Vector of selected jpegs indexes
     */
    SlideShowJpegCommand(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> &indexes);

private:
    /**
     * Default command instruction
     */
    std::vector<unsigned char> kInstruction = {0xec, 0x5d, 0x0, 0x4};
    /**
     * Helper instruction to set a jpeg index for the slideshow
     */
    std::vector<unsigned char> kDefaultJpegCommand = {0x4, 0x0, 0x3, 0x5};
    /**
     * jpeg index on kDefaultJpegCommand instruction
     */
    const int kJpegIndex = 2;
    /**
     * Index (kDefaultJpegCommand) to increment with each selected jpeg
     */
    const int kIncrementIndex = 1;
};

#endif // RYUJINIII_SLIDESHOW_JPEG_COMMAND_H
