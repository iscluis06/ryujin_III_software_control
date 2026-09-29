#ifndef RYUJINIII_START_JPEG_SELECTION_COMMAND_H
#define RYUJINIII_START_JPEG_SELECTION_COMMAND_H

#include "commands/base_command.h"

class StartInstructionCommand : public BaseCommand {
public:
    StartInstructionCommand(std::shared_ptr<LibUsbWrapperBase> base);
    std::string GetClassName() const override;

private:
    std::vector<unsigned char> kInstruction = {0xec, 0xdc};
};

#endif // RYUJINIII_START_JPEG_SELECTION_COMMAND_H
