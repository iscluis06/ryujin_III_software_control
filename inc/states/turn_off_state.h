#ifndef RYUJINIII_TURN_OFF_STATE_H
#define RYUJINIII_TURN_OFF_STATE_H
#include "base_state.h"

class TurnOffState: BaseState {
public:
    TurnOffState(std::shared_ptr<libusb_device_handle *> device);
    bool Execute() override;
private:
    const unsigned char kTurnOff[2] = {0xec, 0x51};
};

#endif //RYUJINIII_TURN_OFF_STATE_H
