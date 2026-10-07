#ifndef RYUJINIII_SLIDESHOW_COMMAND_H
#define RYUJINIII_SLIDESHOW_COMMAND_H

#include "commands/base_command.h"
/**
 * Slide show command (gifs)
 */
class SlideShowCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     * @param gifs Vector of selected gif indexes
     */
    SlideShowCommand(std::shared_ptr<LibUsbWrapperBase> base, std::vector<int> gifs);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default instruction command
     */
    std::vector<unsigned char> kInstruction = {0xec, 0x5d, 0x0, 0x4};
    /**
     * Helper instruction to set a gif index for the slideshow
     */
    std::vector<unsigned char> kDefaultGifCommand = {0x10, 0x1, 0x0, 0x5};
    /**
     * Gif index on kDefaultGifCommand instruction
     */
    const int kGifIndex = 2;
    /**
     * Max number of gifs to select
     */
    const int kMaxGifs = 10;
};

#endif // RYUJINIII_SLIDESHOW_COMMAND_H
