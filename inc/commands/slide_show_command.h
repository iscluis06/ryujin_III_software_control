#ifndef RYUJINIII_SLIDESHOW_COMMAND_H
#define RYUJINIII_SLIDESHOW_COMMAND_H

#include "commands/base_command.h"

class SlideShowCommand : public BaseCommand {
public:
    SlideShowCommand(std::shared_ptr<LibUsbWrapperBase> base, std::vector<int> gifs);
    std::string GetClassName() const override;

private:
    std::vector<unsigned char> kInstruction = {0xec, 0x5d, 0x0, 0x4};
    std::vector<unsigned char> default_gif_command = {0x10, 0x1, 0x0, 0x5};
    const int kGifIndex = 2;
    const int kMaxGifs = 10;
};

#endif // RYUJINIII_SLIDESHOW_COMMAND_H
