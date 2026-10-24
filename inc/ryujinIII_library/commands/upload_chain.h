#ifndef RYUJINIII_UPLOAD_CHAIN_H
#define RYUJINIII_UPLOAD_CHAIN_H

#include "command_chain.h"
#include "stores/memory_slots_store.h"
#include "tools/transform_tool_base.h"
#include "utils/file_handle_base.h"

/**
 * Command chain to upload a gif file
 */
class UploadChain : public CommandChain {
public:
    /**
     * Constructor which sets all required command properties
     * @param transform_tool Transforming tool reference, <br>@warning this functionality may change in the future.
     * @param file_tool File handling tool
     * @param wrapper Reference to libusb wrapper
     * @param path Path to the gif file to upload
     * @param memory_index Memory space where to upload gif
     * @param store Memory Slot instance
     */
    UploadChain(std::shared_ptr<TransformToolBase> transform_tool, std::shared_ptr<FileHandleBase> file_tool,
                std::shared_ptr<LibUsbWrapperBase> wrapper, const std::string &path, int memory_index,
                std::shared_ptr<MemorySlotsStoreBase> store);

    /**
     * Execution of chain commands
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Max number of tries before canceling command
     */
    const int kMaxTries_ = 3;
    /**
     * Property to keep track of selected index
     */
    int index_;
    /**
     * Reference to file handle tool
     */
    std::shared_ptr<FileHandleBase> file_tool_;
    /**
     * Property for MemorySlotStoreBase instance
     */
    std::shared_ptr<MemorySlotsStoreBase> store_;
};

#endif // RYUJINIII_UPLOAD_CHAIN_H
