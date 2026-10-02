#ifndef RYUJINIII_UPLOAD_CHAIN_JPEG_H
#define RYUJINIII_UPLOAD_CHAIN_JPEG_H

#include "command_chain.h"
#include "file_handle_base.h"
#include "transform_tool_base.h"

/**
 * Command chain to upload a gif file
 */
class UploadChainJpeg : public CommandChain {
public:
    /**
     * Constructor which sets all required command properties
     * @param transform_tool Transforming tool reference, <br>@warning this functionality may change in the future.
     * @param file_tool File handling tool
     * @param wrapper Reference to libusb wrapper
     * @param path Path to the gif file to upload
     * @param memory_index Memory space where to upload gif
     */
    UploadChainJpeg(std::shared_ptr<TransformToolBase> transform_tool, std::shared_ptr<FileHandleBase> file_tool,
                    std::shared_ptr<LibUsbWrapperBase> wrapper, const std::string &path, int memory_index);

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
    std::shared_ptr<FileHandleBase> file_tool_;
    int index_;
};

#endif // RYUJINIII_UPLOAD_CHAIN_JPEG_H
