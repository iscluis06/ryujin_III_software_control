#ifndef RYUJINIII_PUMP_SPEED_COMMAND_H
#define RYUJINIII_PUMP_SPEED_COMMAND_H

#include <memory>
#include "base_command.h"
#include "wrappers/libusb_wrapper_base.h"

/**
 * Speed config command (for pump and fans)
 */
class SpeedConfigCommand : public BaseCommand {
public:
    /**
     * Enum to select pump or fan device
     */
    enum class DeviceSelector { PUMP_DEVICE, FAN_DEVICE };
    /**
     * Default constructor
     * @param wrapper Reference to libusb wrapper
     * @param device_selector Device selector choice
     * @param speed Selected speed (refeer to README)
     */
    SpeedConfigCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, DeviceSelector device_selector, int speed);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;
    /**
     * Default method to execute command.
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default command instruction
     */
    std::vector<unsigned char> kDefaultInstruction_ = {0xec, 0x1a, 0x01};
    /**
     * Pump speed index (KDefaultInstruction)
     */
    static constexpr int kPumpSpeedOffset_ = 3;
    /**
     * Fan speed index (KDefaultInstruction)
     */
    static constexpr int kFanSpeedOffset_ = 4;
    /**
     * Property to keep track of selected device
     */
    DeviceSelector device_selected_;
    /**
     * Property to keep track of selected speed
     */
    int speed_;
    /**
     * Returns a calculated speed according to selected DEVICE (the opposite device from device_selected will be used).
     * @param value Current value for a given speed, if PUMP_DEVICE selected then FAN_DEVICE will used, otherwise
     * PUMP_DEVICE.
     * @return The calculated index for the speed of DEVICE
     */
    int DefaultSpeedConfig(int value);
};
#endif // RYUJINIII_PUMP_SPEED_COMMAND_H
