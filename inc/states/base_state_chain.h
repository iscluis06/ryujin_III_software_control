#ifndef RYUJINIII_BASE_STATE_CHAIN_H
#define RYUJINIII_BASE_STATE_CHAIN_H

class BaseStateChain {
public:
    BaseStateChain() = default;

    virtual bool Execute() = 0;
};

#endif //RYUJINIII_BASE_STATE_CHAIN_H
