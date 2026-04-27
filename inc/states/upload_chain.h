#ifndef RYUJINIII_UPLOAD_CHAIN_H
#define RYUJINIII_UPLOAD_CHAIN_H

#include "states/state_chain.h"
#include "file_handle.h"

class UploadChain : public StateChain {
public:
    UploadChain(std::shared_ptr<libusb_device_handle *> device, const std::string &path,
                int memory_index);

private:
    static const bool retry_ = true;
    static const int kMaxTries_ = 50;
    FileHandle file_handle;
};

#endif //RYUJINIII_UPLOAD_CHAIN_H
