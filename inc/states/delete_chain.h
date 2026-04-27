#ifndef RYUJINIII_DELETE_CHAIN_H
#define RYUJINIII_DELETE_CHAIN_H
#include "state_chain.h"
#include <libusb-1.0/libusb.h>
#include <memory>

class DeleteChain : public StateChain {
public:
    DeleteChain(std::shared_ptr<libusb_device_handle *> device, int memory_index);

private:
    static const bool retry_ = true;
    static const int kMaxTries_ = 3;
};

#endif //RYUJINIII_DELETE_CHAIN_H
