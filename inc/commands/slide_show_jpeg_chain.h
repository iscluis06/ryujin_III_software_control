#ifndef RYUJINIII_SLIDE_SHOW_JPEG_CHAIN_H
#define RYUJINIII_SLIDE_SHOW_JPEG_CHAIN_H

#include "commands/command_chain.h"

class SlideShowJpegChain : public CommandChain {
public:
    SlideShowJpegChain(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> &indexes);
    bool Execute() override;

private:
    /**
     * Default number of tries before canceling command retries
     */
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_SLIDE_SHOW_JPEG_CHAIN_H
