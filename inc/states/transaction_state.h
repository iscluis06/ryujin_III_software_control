#ifndef RYUJINIII_TRANSACTION_STATE_H
#define RYUJINIII_TRANSACTION_STATE_H

#include "states/base_state.h"
#include <libusb-1.0/libusb.h>
#include <memory>

class TransactionState : public BaseState {
public:
    TransactionState(std::shared_ptr<libusb_device_handle *> device);

    bool Execute() override;

private:
    const unsigned char kTransaction[4] = {0xec, 0x71, 0x01, 0x01};
    const unsigned char kValidateResponse[2] = {0xec, 0x71};
};

#endif //RYUJINIII_TRANSACTION_STATE_H
