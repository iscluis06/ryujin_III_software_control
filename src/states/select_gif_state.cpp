#include "states/select_gif_state.h"
#include "libusb_wrapp.h"

SelectGifState::SelectGifState(std::shared_ptr<libusb_device_handle *> device): BaseState(device) {
}

bool SelectGifState::Execute(unsigned char endpoint, std::vector<unsigned char> &message) {
    LibUsbWrapp wrapp(this->GetDevice(), this->kTimeout);
    return wrapp.SendInterrupt(endpoint,message);
}
