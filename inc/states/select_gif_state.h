#ifndef RYUJINIII_SELECT_GIF_STATE_H
#define RYUJINIII_SELECT_GIF_STATE_H
#include "base_state.h"

class SelectGifState: public BaseState {
public:
    SelectGifState(std::shared_ptr<libusb_device_handle *> device);
    bool Execute(unsigned char endpoint, std::vector<unsigned char> &message) override;
private:
    const unsigned char kSelectGif[4] = {0xec, 0x51, 0x10, 0x01};
};

#endif //RYUJINIII_SELECT_GIF_STATE_H
