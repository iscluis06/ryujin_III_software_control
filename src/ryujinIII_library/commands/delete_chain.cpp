#include "commands/delete_chain.h"

#include "commands/default_gif_command.h"
#include "commands/delete_command.h"
#include "commands/select_memory_space_command.h"

DeleteChain::DeleteChain(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index,
                         std::shared_ptr<MemorySlotsStoreBase> store, RyujinConstants::Slots type) : CommandChain() {
    this->type_ = type == RyujinConstants::Slots::GIF ? RyujinConstants::Slots::GIF : RyujinConstants::Slots::JPEG;
    this->AddCommand(new DefaultGifCommand(wrapper));
    this->AddCommand(new SelectMemorySpaceCommand(wrapper, memory_index, type));
    this->AddCommand(new DeleteCommand(wrapper));
    this->index_ = memory_index;
    this->store_ = std::move(store);
}

bool DeleteChain::Execute() {
    int no_retries = 0;
    bool result = false;
    while (no_retries < this->kMaxTries_) {
        if (this->CommandChain::Execute()) {
            result = true;
            break;
        }
        no_retries++;
    }
    store_->RemoveSlot(this->index_, this->type_);
    store_->UpdateSlots();
    return result;
}
