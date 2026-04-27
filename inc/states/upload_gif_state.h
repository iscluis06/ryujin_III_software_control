#ifndef RYUJINIII_UPLOAD_GIF_STATE_H
#define RYUJINIII_UPLOAD_GIF_STATE_H

#include "states/base_state.h"
#include <memory>
#include <libusb-1.0/libusb.h>

#include "file_handle.h"

class UploadGifState : public BaseState {
public:
    UploadGifState(std::shared_ptr<libusb_device_handle *> device, const FileHandle &file_handle);

    bool Execute() override;

private:
    const unsigned char kValidateResponse[5] = {0xee, 0x14, 0x0, 0x0, 0x10};
    const FileHandle &file_handle;
};

#endif //RYUJINIII_UPLOAD_GIF_STATE_H
