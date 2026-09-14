#ifndef RYUJINIII_HARDWARE_STATUS_COMMAND_H
#define RYUJINIII_HARDWARE_STATUS_COMMAND_H

#include "byte_utils.h"
#include "commands/base_command.h"
#include "stores/hardware_status_store.h"

class HardwareStatusCommand : public BaseCommand {
public:
    HardwareStatusCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, std::shared_ptr<HardwareStatusStore> store);
    void UpdateStore();
    std::string GetClassName() const override;

private:
    std::shared_ptr<HardwareStatusStore> store_;
    const std::vector<unsigned char> kStatusCommand_ = {0xec, 0x99, 0x19};
    const int kPumpSpeedOffset_ = 7;
    const int kPumpFanSpeedOffset_ = 10;
    const int kTempOffset_ = 5;
    ByteUtils byte_utils;
};

#endif // RYUJINIII_HARDWARE_STATUS_COMMAND_H
