#ifndef RYUJINIII_CLOCK_CHAIN_H
#define RYUJINIII_CLOCK_CHAIN_H

#include "commands/command_chain.h"

/**
 * Class to handle the clock mode configuration for ryujin display.
 */
class ClockChain : public CommandChain {
public:
    /**
     * Default constructor
     * @param base Wrapper to libusb library
     */
    ClockChain(std::shared_ptr<LibUsbWrapperBase> base);
    /**
     * Method that executes the clock mode on ryujin led display
     * @return
     */
    bool Execute() override;

private:
    /**
     * Maximum number of tries for the command chain.
     */
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_CLOCK_CHAIN_H
