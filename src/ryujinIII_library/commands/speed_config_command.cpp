#include "commands/speed_config_command.h"

#include <fstream>

#include "commands/hardware_status_command.h"
SpeedConfigCommand::SpeedConfigCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int pump_speed, int fan_speed) :
    BaseCommand(std::move(wrapper)) {
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->ShouldReadBack(true);
    this->speed1_ = pump_speed;
    this->speed2_ = fan_speed;
    device_selected_ = RyujinConstants::DeviceSelector::BOTH;
}
SpeedConfigCommand::SpeedConfigCommand(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                       RyujinConstants::DeviceSelector device_selector, int speed) :
    BaseCommand(std::move(wrapper)) {
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    device_selected_ = device_selector;
    speed1_ = speed;
    this->ShouldReadBack(true);
}

bool SpeedConfigCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->kDefaultInstruction_.data(), this->kDefaultInstruction_.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    if (device_selected_ == RyujinConstants::DeviceSelector::BOTH) {
        buffer[SpeedConfigCommand::kFanSpeedOffset_] = this->speed2_;
        buffer[SpeedConfigCommand::kPumpSpeedOffset_] = this->speed1_;
    }else {
        std::shared_ptr<HardwareStatusStore> store = std::make_shared<HardwareStatusStore>();
        HardwareStatusCommand status_command(this->GetWrapper(), store);
        status_command.Execute();
        if (device_selected_ == RyujinConstants::DeviceSelector::FAN_DEVICE) {
            buffer[SpeedConfigCommand::kFanSpeedOffset_] = speed1_;
            buffer[SpeedConfigCommand::kPumpSpeedOffset_] = DefaultSpeedConfig(store->GetPumpSpeed());
        } else if (device_selected_ == RyujinConstants::DeviceSelector::PUMP_DEVICE) {
            buffer[SpeedConfigCommand::kPumpSpeedOffset_] = speed1_;
            buffer[SpeedConfigCommand::kFanSpeedOffset_] = DefaultSpeedConfig(store->GetFanSpeed());
        }
    }
    this->SetInstruction(buffer);

    return BaseCommand::Execute();
}

std::string SpeedConfigCommand::GetClassName() const { return "PumpSpeedCommand"; }
int SpeedConfigCommand::DefaultSpeedConfig(int value) {
    int result = 0;
    if (this->device_selected_ != RyujinConstants::DeviceSelector::PUMP_DEVICE) {
        result = ((value - 870) / 43) + 21;
    }
    if (this->device_selected_ != RyujinConstants::DeviceSelector::FAN_DEVICE) {
        result = ((value - 660) / 65) + 26;
    }
    return result;
}
