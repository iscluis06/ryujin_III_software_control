#include "commands/show_slots_command.h"

ShowSlotsCommand::ShowSlotsCommand(std::shared_ptr<MemorySlotsStore> store) : store_(std::move(store)) {}

bool ShowSlotsCommand::Execute() {
    store_->PrintAll();
    return true;
}
std::string ShowSlotsCommand::GetClassName() const { return "ShowSlotsCommand"; }
