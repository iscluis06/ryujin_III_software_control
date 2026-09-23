#ifndef RYUJINIII_PUMP_SPEED_COMMAND_H
#define RYUJINIII_PUMP_SPEED_COMMAND_H

#include <memory>
#include "base_command.h"
#include "wrappers/libusb_wrapper_base.h"

class SpeedConfigCommand : public BaseCommand {
public:
    enum class DeviceSelector { PUMP_DEVICE, FAN_DEVICE };
    SpeedConfigCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, DeviceSelector device_selector, int speed);
    std::string GetClassName() const override;
    bool Execute() override;

private:
    std::vector<unsigned char> default_instruction_ = {0xec, 0x1a, 0x01};
    static constexpr int pump_speed_offset_ = 3;
    static constexpr int fan_speed_offset_ = 4;
    DeviceSelector device_selected_;
    int speed_;
    int DefaultSpeedConfig(int value);
};
#endif // RYUJINIII_PUMP_SPEED_COMMAND_H
