#ifndef RYUJINIII_SLIDE_SHOW_CHAIN_H
#define RYUJINIII_SLIDE_SHOW_CHAIN_H

#include <vector>
#include "command_chain.h"

class SlideShowChain : public CommandChain {
public:
    SlideShowChain(std::shared_ptr<LibUsbWrapperBase> wrapper, std::vector<int> gifs);
    bool Execute() override;

private:
    const int kMaxTries_ = 3;
};

#endif // RYUJINIII_SLIDE_SHOW_CHAIN_H
