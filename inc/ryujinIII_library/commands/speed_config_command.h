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
     * Constructor to set both devices speeds
     * @param wrapper Reference to libusb wrapper
     * @param pump_speed Selected speed for pump
     * @param fan_speed Selected speed for fans
     */
    SpeedConfigCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int pump_speed, int fan_speed);
    /**
     * Constructor to only set one device speed config
     * @param wrapper Reference to libusb wrapper
     * @param device_selector Device selector choice
     * @param speed Selected speed (refeer to README)
     */
    SpeedConfigCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, RyujinConstants::DeviceSelector device_selector,
                       int speed);
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
    RyujinConstants::DeviceSelector device_selected_;
    /**
     * Property to keep track of selected speed
     */
    int speed1_ = 0;
    /**
     * Property to keep track of selected speed
     */
    int speed2_ = 0;
    /**
     * Returns a calculated speed according to selected DEVICE (the opposite device from device_selected will be used).
     * @param value Current value for a given speed, if PUMP_DEVICE selected then FAN_DEVICE will used, otherwise
     * PUMP_DEVICE.
     * @return The calculated index for the speed of DEVICE
     */
    int DefaultSpeedConfig(int value);
};
#endif // RYUJINIII_PUMP_SPEED_COMMAND_H
