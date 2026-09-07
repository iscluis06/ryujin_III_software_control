#ifndef RYUJINIII_UPLOAD_GIF_COMMAND_H
#define RYUJINIII_UPLOAD_GIF_COMMAND_H

#include <memory>
#include "base_command.h"

#include "file_handle.h"

/**
 * Command to upload a gif file
 */
class UploadGifCommand : public BaseCommand {
public:
    /**
     * Constructor which sets the wrapper and file handle properties
     * @param wrapper Reference to libusb wrapper
     * @param file_handle Reference to file handle
     */
    UploadGifCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, std::shared_ptr<FileHandleBase> file_handle);

    /**
     * Default command execution
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default command instruction
     */
    const unsigned char kValidateResponse[5] = {0xee, 0x14, 0x0, 0x0, 0x10};
    /**
     * File handle
     */
    std::shared_ptr<FileHandleBase> file_handle_;
};

#endif // RYUJINIII_UPLOAD_GIF_COMMAND_H
