#ifndef RYUJINIII_TURN_ON_STATE_H
#define RYUJINIII_TURN_ON_STATE_H

#include "states/base_state.h"

class TurnOnState: BaseState {
public:
    TurnOnState(std::shared_ptr<libusb_device_handle *> device);
    bool Execute() override;
private:
    const unsigned char kTurnOn[3] = {0xec, 0x51, 0x14};
};

#endif //RYUJINIII_TURN_ON_STATE_H
