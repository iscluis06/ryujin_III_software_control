#ifndef RYUJINIII_START_JPEG_SELECTION_COMMAND_H
#define RYUJINIII_START_JPEG_SELECTION_COMMAND_H

#include "commands/base_command.h"

class StartJpegSelectionCommand : public BaseCommand {
public:
    StartJpegSelectionCommand(std::shared_ptr<LibUsbWrapperBase> base);
    std::string GetClassName() const override;

private:
    std::vector<unsigned char> kStartJpegSelectionCommand = {0xec, 0xdc};
};

#endif // RYUJINIII_START_JPEG_SELECTION_COMMAND_H
