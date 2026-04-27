#ifndef RYUJINIII_DELETE_STATE_H
#define RYUJINIII_DELETE_STATE_H
#include "base_state.h"

class DeleteState : public BaseState {
public:
    DeleteState(std::shared_ptr<libusb_device_handle *> device);

    bool Execute() override;

private:
    const unsigned char kDelete[3] = {0xec, 0x73, 0x03};
    const unsigned char kValidateResponse[2] = {0xec, 0x73};
};

#endif //RYUJINIII_DELETE_STATE_H
