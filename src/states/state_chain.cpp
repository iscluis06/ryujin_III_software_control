#include "states/state_chain.h"

#include <iostream>

StateChain::StateChain(bool retry, int retries) : retry_(retry), retries_(retries) {
}

bool StateChain::Execute() {
    if (this->states_.empty()) {
        std::cerr << "States list is empty" << std::endl;
        return false;
    }
    int retries = 1;
    while (this->current_state_ != this->states_.end()) {
        bool result = this->current_state_->get()->Execute();
        if (!result && (!this->retry_ || this->retries_ == retries)) {
            return false;
        } else if (!result) {
            this->current_state_ = this->states_.begin();
            retries++;
        } else {
            std::advance(this->current_state_, 1);
        }
    }
    return true;
}

void StateChain::SetStateList(std::list<std::shared_ptr<BaseState> > states) {
    this->states_ = std::move(states);
    this->current_state_ = this->states_.begin();
}
