#ifndef RYUJINIII_SLIDE_SHOW_CHAIN_H
#define RYUJINIII_SLIDE_SHOW_CHAIN_H

#include <vector>
#include "command_chain.h"

/**
 * Slideshow chain command (gifs)
 */
class SlideShowChain : public CommandChain {
public:
    /**
     * Default constructor
     * @param wrapper Reference to libusb wrapper
     * @param gifs Vector of selected gif indexes (0-9)
     */
    SlideShowChain(std::shared_ptr<LibUsbWrapperBase> wrapper, std::vector<int> gifs);
    /**
     * Default command execution
     * @return Returns true on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Max number of tries before canceling command
     */
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_SLIDE_SHOW_CHAIN_H
