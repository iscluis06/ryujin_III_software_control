#ifndef RYUJINIII_SELECT_MEMORY_SPACE_STATE_H
#define RYUJINIII_SELECT_MEMORY_SPACE_STATE_H
#include "base_state.h"

class SelectMemorySpaceState : public BaseState {
public:
    SelectMemorySpaceState(std::shared_ptr<libusb_device_handle *> device, int memory_index);

    bool Execute() override;

private:
    int memory_index_;
    const unsigned char kSelectMemory[4] = {0xec, 0x72, 0x01, 0x02};
    const unsigned char kValidateResponse[2] = {0xec, 0x72};
};

#endif //RYUJINIII_SELECT_MEMORY_SPACE_STATE_H
