#ifndef RYUJINIII_START_TRANSACTION_STATE_H
#define RYUJINIII_START_TRANSACTION_STATE_H

#include "states/base_state.h"


class StartTransactionState : public BaseState {
public:
    StartTransactionState(std::shared_ptr<libusb_device_handle *> device);

    bool Execute() override;

private:
    const unsigned char kStartTransaction[2] = {0xec, 0xf1};
    const unsigned char kValidateResponse[8] = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
};

#endif //RYUJINIII_START_TRANSACTION_STATE_H
