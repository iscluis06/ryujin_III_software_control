#ifndef RYUJINIII_SLIDE_SHOW_JPEG_CHAIN_H
#define RYUJINIII_SLIDE_SHOW_JPEG_CHAIN_H

#include "commands/command_chain.h"

/**
 * Slideshow chain command (jpegs)
 */
class SlideShowJpegChain : public CommandChain {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     * @param indexes Vector of selected jpegs indexes (0-9)
     */
    SlideShowJpegChain(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> &indexes);
    /**
     * Execution of chain commands
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default number of tries before canceling command retries
     */
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_SLIDE_SHOW_JPEG_CHAIN_H
