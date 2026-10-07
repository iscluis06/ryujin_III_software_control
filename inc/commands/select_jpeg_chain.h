#ifndef RYUJINIII_SELECT_JPEG_CHAIN_H
#define RYUJINIII_SELECT_JPEG_CHAIN_H

#include "commands/command_chain.h"

/**
 * Select JPEG Instruction
 */
class SelectJpegChain : public CommandChain {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     * @param index Index to upload jpeg image
     */
    SelectJpegChain(std::shared_ptr<LibUsbWrapperBase> base, int index);
    /**
     * Default implementation of execution of chain commands
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Max number of tries before canceling command
     */
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_SELECT_JPEG_CHAIN_H
