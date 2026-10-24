#include "commands/select_memory_space_command.h"

#include "ryujin/ryujin_constants.h"

SelectMemorySpaceCommand::SelectMemorySpaceCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index,
                                                   RyujinConstants::Slots type) : BaseCommand(std::move(wrapper)) {
    auto buffer = this->GetWrapper()->FillArray(this->kSelectMemory.data(), this->kSelectMemory.size(),
                                                RyujinConstants::kDefaultInterruptDataLength);
    int type_slot = type == RyujinConstants::Slots::GIF ? 2 : 1;
    buffer[kMemoryTypeIndex] = static_cast<unsigned char>(type_slot);
    buffer[4] = memory_index;
    this->SetInstruction(buffer);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetTimeout(20);
    this->ShouldReadBack(true);
    this->SetValidationMessage(this->kValidateResponse);
}

std::string SelectMemorySpaceCommand::GetClassName() const { return "SelectMemorySpaceCommand"; }
