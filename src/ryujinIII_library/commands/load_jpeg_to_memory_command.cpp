#include "commands/load_jpeg_to_memory_command.h"

LoadJPEGToMemoryCommand::LoadJPEGToMemoryCommand(std::shared_ptr<LibUsbWrapperBase> base, int index, int instruction) :
    BaseCommand(std::move(base)) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->kInstruction[this->kMemorySlotIndex] = index;
    this->kInstruction[this->kInstructionIndex] = instruction;
    this->SetInstruction(this->kInstruction);
}
std::string LoadJPEGToMemoryCommand::GetClassName() const { return "LoadJPEGToMemoryCommand"; }
