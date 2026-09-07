#ifndef RYUJINIII_DELETE_CHAIN_H
#define RYUJINIII_DELETE_CHAIN_H
#include <memory>
#include "command_chain.h"

/**
 * Command chain to delete a gif from memory (1-10)
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
     */
    DeleteChain(std::shared_ptr<LibUsbWrapperBase> wrapper, int memory_index);

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
};

#endif // RYUJINIII_DELETE_CHAIN_H
