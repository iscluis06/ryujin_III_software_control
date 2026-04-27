#ifndef RYUJINIII_START_UPLOAD_STATE_H
#define RYUJINIII_START_UPLOAD_STATE_H

#include "states/base_state.h"
#include <libusb-1.0/libusb.h>
#include <memory>

class StartUploadState : public BaseState {
public:
    StartUploadState(std::shared_ptr<libusb_device_handle *> device);

    bool Execute() override;

private:
    const unsigned char kStartUpload[3] = {0xec, 0x73, 0x01};
    const unsigned char kValidateResponse[2] = {0xec, 0x73};
};

#endif //RYUJINIII_START_UPLOAD_STATE_H
