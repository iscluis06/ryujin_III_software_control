#include "states/delete_chain.h"
#include "states/select_memory_space_state.h"
#include "states/delete_state.h"

DeleteChain::DeleteChain(std::shared_ptr<libusb_device_handle *> device, int memory_index) : StateChain(
    DeleteChain::retry_, DeleteChain::kMaxTries_) {
    std::list<std::shared_ptr<BaseState> > states;
    states.emplace_back(std::make_shared<SelectMemorySpaceState>(device, memory_index));
    states.emplace_back(std::make_shared<DeleteState>(device));
    this->SetStateList(states);
}
