#ifndef RYUJINIII_SELECT_JPEG_CHAIN_H
#define RYUJINIII_SELECT_JPEG_CHAIN_H

#include "commands/command_chain.h"

class SelectJpegChain : public CommandChain {
public:
    SelectJpegChain(std::shared_ptr<LibUsbWrapperBase> base, int index);
    bool Execute() override;

private:
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_SELECT_JPEG_CHAIN_H
