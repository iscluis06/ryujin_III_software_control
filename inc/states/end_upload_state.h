#ifndef RYUJINIII_END_UPLOAD_STATE_H
#define RYUJINIII_END_UPLOAD_STATE_H

#include "states/base_state.h"
#include <memory>
#include <libusb-1.0/libusb.h>

class EndUploadState : public BaseState {
public:
    EndUploadState(std::shared_ptr<libusb_device_handle *> device);

    bool Execute() override;

private:
    const unsigned char kEndUpload[3] = {0xec, 0x73, 0xff};
    const unsigned char kValidateResponse[2] = {0xec, 0x73};
};


#endif //RYUJINIII_END_UPLOAD_STATE_H
