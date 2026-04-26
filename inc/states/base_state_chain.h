#ifndef RYUJINIII_BASE_STATE_CHAIN_H
#define RYUJINIII_BASE_STATE_CHAIN_H
#include "base_state.h"
#include <list>

class BaseStateChain {
public:
    BaseStateChain(bool retry, std::List<BaseState *> states, int retries = 0);
    bool Execute();
private:
    std::List<BaseState *> states_;
    bool retry_;
    int retries_;
};

#endif //RYUJINIII_BASE_STATE_CHAIN_H
