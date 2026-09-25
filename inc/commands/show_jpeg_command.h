#ifndef RYUJINIII_SHOW_JPEG_COMMAND_H
#define RYUJINIII_SHOW_JPEG_COMMAND_H

#include "commands/base_command.h"

class ShowJpegCommand : public BaseCommand {
public:
    ShowJpegCommand(std::shared_ptr<LibUsbWrapperBase> base, int index);
    std::string GetClassName() const override;

private:
    std::vector<unsigned char> kShowJpegCommand = {0xec, 0x5d, 0x0, 0x1, 0x4, 0x0, 0x6, 0x5};
    const int kShowJpegIndex = 6;
};

#endif // RYUJINIII_SHOW_JPEG_COMMAND_H
