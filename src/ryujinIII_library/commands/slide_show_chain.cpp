#include "commands/slide_show_chain.h"

#include "commands/end_instruction_command.h"
#include "commands/slide_show_command.h"
#include "commands/start_instruction_command.h"
SlideShowChain::SlideShowChain(std::shared_ptr<LibUsbWrapperBase> wrapper, const std::vector<int> gifs) {
    this->AddCommand(new StartInstructionCommand(wrapper));
    this->AddCommand(new SlideShowCommand(wrapper, gifs));
    this->AddCommand(new EndInstructionCommand(wrapper));
}
bool SlideShowChain::Execute() {
    int no_retries = 0;
    while (no_retries < this->kMaxTries_) {
        if (this->CommandChain::Execute()) {
            return true;
        }
        no_retries++;
    }
    return false;
}
