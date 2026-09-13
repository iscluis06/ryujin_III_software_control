#include "commands/hardware_monitor_line_command.h"

#include "ryujin_constants.h"
HardwareMonitorLineCommand::HardwareMonitorLineCommand(const std::shared_ptr<LibUsbWrapperBase> &wrapper,
                                                       std::shared_ptr<LedLineBase> base, int line) :
    BaseCommand(wrapper) {
    this->line_ = line;
    this->base_ = base;
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->ShouldReadBack(true);
}
bool HardwareMonitorLineCommand::Execute() {
    std::vector<unsigned char> title = byte_utils_.ReturnASCII(this->base_->GetTitle());
    title = this->GetWrapper()->FillArray(title.data(), title.size(), 18);
    std::vector<unsigned char> value = byte_utils_.ReturnASCII(this->base_->GetLine());
    value = this->GetWrapper()->FillArray(value.data(), value.size(), 12);
    std::vector<unsigned char> instruction;
    instruction.insert(instruction.end(), this->line_command.begin(), this->line_command.end());
    instruction.insert(instruction.end(), std::make_move_iterator(title.begin()), std::make_move_iterator(title.end()));
    instruction.insert(instruction.end(), std::make_move_iterator(value.begin()), std::make_move_iterator(value.end()));
    instruction[2] = this->line_;
    this->SetInstruction(this->GetWrapper()->FillArray(instruction.data(), instruction.size(),
                                                       RyujinConstants::kDefaultInterruptDataLength));
    return BaseCommand::Execute();
}
