#include "commands/clock_mode_command.h"
#include <cstring>

ClockModeCommand::ClockModeCommand(std::shared_ptr<LibUsbWrapperBase> base) : BaseCommand(std::move(base)) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->ShouldReadBack(true);
    this->current_time_ = std::time({});
    this->kInstruction[kHourIndex] = this->GetHourDecimalValue();
    this->kInstruction[kMinuteIndex] = this->GetMinuteDecimalValue();
    this->kInstruction[kSecondsIndex] = this->GetSecondDecimalValue();
    this->kInstruction[kTimePeriod] = static_cast<unsigned char>(this->GetPMOrAM());
    this->SetInstruction(kInstruction);
}
std::string ClockModeCommand::GetClassName() const { return "ClockModeCommand"; }
int ClockModeCommand::GetHourDecimalValue() {
    char hourString[3];
    std::strftime(std::data(hourString), std::size(hourString), "%I", std::localtime(&this->current_time_));
    return this->byteutils_.GetDecimalValueFromHexString(hourString);
}
int ClockModeCommand::GetMinuteDecimalValue() {
    char minuteString[3];
    std::strftime(std::data(minuteString), std::size(minuteString), "%M", std::localtime(&this->current_time_));
    return this->byteutils_.GetDecimalValueFromHexString(minuteString);
}
int ClockModeCommand::GetSecondDecimalValue() {
    char secondString[3];
    std::strftime(std::data(secondString), std::size(secondString), "%S", std::localtime(&this->current_time_));
    return this->byteutils_.GetDecimalValueFromHexString(secondString);
}
ClockModeCommand::TimePeriod ClockModeCommand::GetPMOrAM() {
    char localizedPm[4] = "AM";
    std::strftime(std::data(localizedPm), std::size(localizedPm), "%p", std::localtime(&this->current_time_));
    if (strcmp(localizedPm, "PM") == 0) {
        return TimePeriod::PM_PERIOD;
    }
    return TimePeriod::AM_PERIOD;
}
