#include "commands/start_instruction_command.h"
StartInstructionCommand::StartInstructionCommand(std::shared_ptr<LibUsbWrapperBase> base) : BaseCommand(base) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetInstruction(kInstruction);
    this->ShouldReadBack(true);
}
std::string StartInstructionCommand::GetClassName() const { return "StartInstructionCommand"; }
