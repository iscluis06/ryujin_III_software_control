#include "commands/clock_chain.h"

#include "commands/clock_mode_command.h"
#include "commands/start_clock_command.h"
ClockChain::ClockChain(std::shared_ptr<LibUsbWrapperBase> base) : CommandChain() {
    this->AddCommand(new ClockModeCommand(base));
    this->AddCommand(new StartClockCommand(base));
}

bool ClockChain::Execute() {
    int no_retries = 0;
    while (no_retries < this->kMaxTries_) {
        if (this->CommandChain::Execute()) {
            return true;
        }
        no_retries++;
    }
    return false;
}
