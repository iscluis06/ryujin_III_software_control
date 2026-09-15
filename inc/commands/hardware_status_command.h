#ifndef RYUJINIII_HARDWARE_STATUS_COMMAND_H
#define RYUJINIII_HARDWARE_STATUS_COMMAND_H

#include "byte_utils.h"
#include "commands/base_command.h"
#include "stores/hardware_status_store.h"
/**
 * Hardware status command to get the information from ryujin sensors.
 * Based on https://github.com/liquidctl findings.
 */
class HardwareStatusCommand : public BaseCommand {
public:
    /**
     * Constructor for hardware status command
     * @param wrapper Reference to libusb wrapper
     * @param store Reference to hardware status store
     */
    HardwareStatusCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, std::shared_ptr<HardwareStatusStore> store);
    /**
     * Updates the store data
     */
    void UpdateStore();
    /**
     * Returns the class name for testing purposes
     * @return the name of the class
     */
    std::string GetClassName() const override;

private:
    /**
     * Reference to hardware status store
     */
    std::shared_ptr<HardwareStatusStore> store_;
    /**
     * Default status command instruction
     */
    const std::vector<unsigned char> kStatusCommand_ = {0xec, 0x99, 0x19};
    /**
     * Offset for pump speed sensor data
     */
    const int kPumpSpeedOffset_ = 7;
    /**
     * Offset for fan speed sensor data
     */
    const int kPumpFanSpeedOffset_ = 10;
    /**
     * Offset for temperature sensor data
     */
    const int kTempOffset_ = 5;
    /**
     * ByteUtils instance
     */
    ByteUtils byte_utils;
};

#endif // RYUJINIII_HARDWARE_STATUS_COMMAND_H
