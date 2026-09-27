#include "commands/end_instruction_command.h"
EndInstructionCommand::EndInstructionCommand(std::shared_ptr<LibUsbWrapperBase> base) : BaseCommand(base) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetInstruction(this->kInstruction);
    this->ShouldReadBack(true);
}
std::string EndInstructionCommand::GetClassName() const { return "EndInstructionCommand"; }
