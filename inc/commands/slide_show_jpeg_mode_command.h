#ifndef RYUJINIII_SLIDE_SHOW_JPEG_MODE_COMMAND_H
#define RYUJINIII_SLIDE_SHOW_JPEG_MODE_COMMAND_H

#include "commands/base_command.h"

class SlideShowJpegModeCommand : public BaseCommand {
public:
    SlideShowJpegModeCommand(std::shared_ptr<LibUsbWrapperBase> base);
    std::string GetClassName() const override;

private:
    std::vector<unsigned char> kInstruction = {0xec, 0x60, 0x3, 0x1, 0x10, 0x2};
};

#endif // RYUJINIII_SLIDE_SHOW_JPEG_MODE_COMMAND_H
