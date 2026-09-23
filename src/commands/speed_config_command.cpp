#include "commands/speed_config_command.h"

#include <fstream>

#include "commands/hardware_status_command.h"

SpeedConfigCommand::SpeedConfigCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, DeviceSelector device_selector,
                                       int speed) : BaseCommand(std::move(wrapper)) {
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    device_selected_ = device_selector;
    speed_ = speed;
    this->ShouldReadBack(true);
}

bool SpeedConfigCommand::Execute() {
    auto buffer = this->GetWrapper()->FillArray(this->default_instruction_.data(), this->default_instruction_.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    std::shared_ptr<HardwareStatusStore> store = std::make_shared<HardwareStatusStore>();
    HardwareStatusCommand status_command(this->GetWrapper(), store);
    status_command.Execute();
    if (device_selected_ == DeviceSelector::FAN_DEVICE) {
        buffer[SpeedConfigCommand::fan_speed_offset_] = speed_;
        buffer[SpeedConfigCommand::pump_speed_offset_] = DefaultSpeedConfig(store->GetPumpSpeed());
    }
    if (device_selected_ == DeviceSelector::PUMP_DEVICE) {
        buffer[SpeedConfigCommand::pump_speed_offset_] = speed_;
        buffer[SpeedConfigCommand::fan_speed_offset_] = DefaultSpeedConfig(store->GetFanSpeed());
    }
    this->SetInstruction(buffer);

    return BaseCommand::Execute();
}

std::string SpeedConfigCommand::GetClassName() const { return "PumpSpeedCommand"; }
int SpeedConfigCommand::DefaultSpeedConfig(int value) {
    int result = 0;
    if (this->device_selected_ != DeviceSelector::PUMP_DEVICE) {
        result = ((value - 870) / 43) + 21;
    }
    if (this->device_selected_ != DeviceSelector::FAN_DEVICE) {
        result = ((value - 660) / 65) + 26;
    }
    return result;
}
