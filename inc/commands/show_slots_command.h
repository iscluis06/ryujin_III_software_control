#ifndef RYUJINIII_SHOW_SLOTS_COMMAND_H
#define RYUJINIII_SHOW_SLOTS_COMMAND_H
#include "base_command.h"
#include "stores/memory_slots_store.h"

/**
 * Helper command to print the available slot according saved data
 */
class ShowSlotsCommand : public ExecuteBase {
public:
    /**
     * Default constructor
     */
    ShowSlotsCommand(std::shared_ptr<MemorySlotsStore> store);
    /**
     * Default command execution
     * @return True on success, False otherwise
     */
    bool Execute() override;
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    std::shared_ptr<MemorySlotsStore> store_;
};

#endif // RYUJINIII_SHOW_SLOTS_COMMAND_H
