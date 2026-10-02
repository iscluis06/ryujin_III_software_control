#include "commands/show_slots_command.h"
#include "stores/memory_slots_store.h"

bool ShowSlotsCommand::Execute() {
    MemorySlotsStore memory_slots_store(RyujinConstants::kRyujinPersistentDirectory);
    memory_slots_store.PrintAll();
    return true;
}
std::string ShowSlotsCommand::GetClassName() const { return "ShowSlotsCommand"; }
