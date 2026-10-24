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
     * @param seconds Seconds that each image will remain on display before changing.
     */
    SlideShowJpegCommand(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> &indexes, int seconds = 5);

private:
    /**
     * Default command instruction
     */
    std::vector<unsigned char> kInstruction = {0xec, 0x5d, 0x0, 0x4};
    /**
     * Helper instruction to set a jpeg index for the slideshow
     */
    // Last digit is the seconds
    std::vector<unsigned char> kDefaultJpegCommand = {0x4, 0x0, 0x1, 0x5};
    /**
     * jpeg index on kDefaultJpegCommand instruction
     */
    const int kJpegIndex = 2;
    const int kSecondsIndex = 3;
    /**
     * Index (kDefaultJpegCommand) to increment with each selected jpeg
     */
    const int kIncrementIndex = 1;
};

#endif // RYUJINIII_SLIDESHOW_JPEG_COMMAND_H
