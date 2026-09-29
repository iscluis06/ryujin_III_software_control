#include "commands/slide_show_jpeg_chain.h"

#include "commands/end_instruction_command.h"
#include "commands/slide_show_jpeg_command.h"
#include "commands/slide_show_jpeg_mode_command.h"
#include "commands/start_instruction_command.h"
SlideShowJpegChain::SlideShowJpegChain(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> &indexes) {
    this->AddCommand(new StartInstructionCommand(base));
    this->AddCommand(new SlideShowJpegModeCommand(base));
    this->AddCommand(new SlideShowJpegCommand(base, indexes));
    this->AddCommand(new EndInstructionCommand(base));
}
bool SlideShowJpegChain::Execute() {
    int no_retries = 0;
    while (no_retries < this->kMaxTries_) {
        if (this->CommandChain::Execute()) {
            return true;
        }
        no_retries++;
    }
    return false;
}
