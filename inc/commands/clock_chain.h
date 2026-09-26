#ifndef RYUJINIII_CLOCK_CHAIN_H
#define RYUJINIII_CLOCK_CHAIN_H

#include "commands/command_chain.h"

class ClockChain : public CommandChain {
public:
    ClockChain(std::shared_ptr<LibUsbWrapperBase> base);
    bool Execute() override;

private:
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_CLOCK_CHAIN_H
