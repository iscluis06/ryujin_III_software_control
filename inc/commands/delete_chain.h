#ifndef RYUJINIII_DELETE_CHAIN_H
#define RYUJINIII_DELETE_CHAIN_H
#include <memory>
#include "command_chain.h"
#include "select_memory_space_command.h"
#include "stores/memory_slots_store.h"


/**
 * Command chain to delete a gif from memory (0-9)
 */
class DeleteChain : public CommandChain {
public:
    /**
     * Default destructor
     */
    ~DeleteChain() override = default;
    /**
     * Deletes a gif from device memory
     * @param wrapper Reference to libusb wrapper
     * @param memory_index Memory index to delete
     * @param type Type of memory slot, by default GIF
     */
    DeleteChain(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index,
                SelectMemorySpaceCommand::MemoryType type = SelectMemorySpaceCommand::MemoryType::GIF);

    /**
     * Execution of chain commands
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default number of tries before canceling command retries
     */
    const int kMaxTries_ = 3;
    /**
     * Property to keep track of selected index
     */
    int index_;
    /**
     * Selected slot type
     */
    MemorySlotsStore::SlotType type_;
};

#endif // RYUJINIII_DELETE_CHAIN_H
