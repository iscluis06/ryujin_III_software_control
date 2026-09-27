#ifndef RYUJINIII_END_JPEG_MODE_COMMAND_H
#define RYUJINIII_END_JPEG_MODE_COMMAND_H

#include "commands/base_command.h"

class EndInstructionCommand : public BaseCommand {
public:
    EndInstructionCommand(std::shared_ptr<LibUsbWrapperBase> base);
    std::string GetClassName() const override;

private:
    const std::vector<unsigned char> kInstruction = {0xec, 0x51, 0x1f};
};

#endif // RYUJINIII_END_JPEG_MODE_COMMAND_H
