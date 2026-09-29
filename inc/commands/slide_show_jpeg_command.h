#ifndef RYUJINIII_SLIDESHOW_JPEG_COMMAND_H
#define RYUJINIII_SLIDESHOW_JPEG_COMMAND_H

#include "commands/base_command.h"

class SlideShowJpegCommand : public BaseCommand {
public:
    std::string GetClassName() const override;
    SlideShowJpegCommand(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> &indexes);

private:
    std::vector<unsigned char> kInstruction = {0xec, 0x5d, 0x0, 0x4};
    std::vector<unsigned char> kDefaultJpegCommand = {0x4, 0x0, 0x3, 0x5};
    const int kJpegIndex = 2;
    const int kIncrementIndex = 1;
};

#endif // RYUJINIII_SLIDESHOW_JPEG_COMMAND_H
