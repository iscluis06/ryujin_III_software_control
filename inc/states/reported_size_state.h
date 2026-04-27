#ifndef RYUJINIII_REPORTED_SIZE_STATE_H
#define RYUJINIII_REPORTED_SIZE_STATE_H

#include "states/base_state.h"
#include <memory>
#include <libusb-1.0/libusb.h>

class ReportedSizeState : public BaseState {
public:
    ReportedSizeState(std::shared_ptr<libusb_device_handle *> device, std::vector<unsigned char> size);

    bool Execute() override;

private:
    const unsigned char kReportedSize[3] = {0xec, 0x7f, 0x02};
    const unsigned char kValidateResponse[5] = {0xec, 0x7f, 0x0, 0x0, 0x10};
    std::vector<unsigned char> size_;
};

#endif //RYUJINIII_REPORTED_SIZE_STATE_H
