#include "commands/select_jpeg_chain.h"

#include "commands/end_jpeg_mode_command.h"
#include "commands/select_jpeg_command.h"
#include "commands/show_jpeg_command.h"
#include "commands/start_jpeg_selection_command.h"

SelectJpegChain::SelectJpegChain(std::shared_ptr<LibUsbWrapperBase> base, int index) {
    this->AddCommand(new StartJpegSelectionCommand(base));
    this->AddCommand(new SelectJpegCommand(base, index));
    this->AddCommand(new ShowJpegCommand(base, index));
    this->AddCommand(new EndJpegModeCommand(base));
}
bool SelectJpegChain::Execute() {
    int no_retries = 0;
    while (no_retries < this->kMaxTries_) {
        if (this->CommandChain::Execute()) {
            return true;
        }
        no_retries++;
    }
    return false;
}
