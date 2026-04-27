#ifndef RYUJINIII_STATE_CHAIN_H
#define RYUJINIII_STATE_CHAIN_H

#include "base_state.h"
#include "base_state_chain.h"
#include <list>

class StateChain : public BaseStateChain {
public:
    StateChain(bool retry, int retries = 0);

    bool Execute() final;

    void SetStateList(std::list<std::shared_ptr<BaseState> > states);

private:
    std::list<std::shared_ptr<BaseState> > states_;
    bool retry_;
    int retries_;
    std::list<std::shared_ptr<BaseState> >::iterator current_state_;
};

#endif //RYUJINIII_STATE_CHAIN_H
