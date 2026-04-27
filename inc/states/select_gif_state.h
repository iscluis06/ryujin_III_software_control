#ifndef RYUJINIII_SELECT_GIF_STATE_H
#define RYUJINIII_SELECT_GIF_STATE_H
#include "base_state.h"

class SelectGifState : public BaseState {
public:
    SelectGifState(std::shared_ptr<libusb_device_handle *> device, int memory_index);

    bool Execute() override;

private:
    const unsigned char kSelectGif[4] = {0xec, 0x51, 0x10, 0x01};
    const unsigned char kValidateResponse[4] = {0xec, 0x51};
    int memory_index_;
};

#endif //RYUJINIII_SELECT_GIF_STATE_H
