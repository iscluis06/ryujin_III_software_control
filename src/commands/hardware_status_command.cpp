#include "commands/hardware_status_command.h"

#include "ryujin_constants.h"

HardwareStatusCommand::HardwareStatusCommand(std::shared_ptr<LibUsbWrapperBase> wrapper,
                                             std::shared_ptr<HardwareStatusStore> store) :
    BaseCommand(std::move(wrapper)), store_(store) {
    this->SetInstruction(this->kStatusCommand_);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->ShouldReadBack(true);
    this->SetCallBackFunction(std::bind(&HardwareStatusCommand::UpdateStore, this));
}
void HardwareStatusCommand::UpdateStore() {
    auto message_back = this->GetMessageBack();
    this->store_->SetLiquidTemp(static_cast<float>(message_back[this->kTempOffset_]) +
                                static_cast<float>(message_back[this->kTempOffset_ + 1]) / 10);
    std::string pump_speed_hex_string_value =
            this->byte_utils.GetHexRepresentation(message_back[kPumpSpeedOffset_ + 1]) +
            this->byte_utils.GetHexRepresentation(message_back[kPumpSpeedOffset_]);
    std::string fan_speed_hex_string_value =
            this->byte_utils.GetHexRepresentation(message_back[kPumpFanSpeedOffset_ + 1]) +
            this->byte_utils.GetHexRepresentation(message_back[kPumpFanSpeedOffset_]);
    this->store_->SetPumpSpeed(this->byte_utils.GetDecimalValueFromHexString(pump_speed_hex_string_value));
    this->store_->SetFanSpeed(this->byte_utils.GetDecimalValueFromHexString(fan_speed_hex_string_value));
}
std::string HardwareStatusCommand::GetClassName() const { return "HardwareStatusCommand"; }
