#include "commands/delete_chain.h"

#include "commands/default_gif_command.h"
#include "commands/delete_command.h"
#include "commands/select_memory_space_command.h"
#include "stores/memory_slots_store.h"

DeleteChain::DeleteChain(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index) : CommandChain() {
    this->AddCommand(new DefaultGifCommand(wrapper));
    this->AddCommand(new SelectMemorySpaceCommand(wrapper, memory_index));
    this->AddCommand(new DeleteCommand(wrapper));
    this->index_ = memory_index;
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
    MemorySlotsStore slots(RyujinConstants::kRyujinPersistentDirectory);
    slots.RemoveSlot(this->index_);
    slots.UpdateSlots();
    return result;
}
