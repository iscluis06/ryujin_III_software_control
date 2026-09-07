#ifndef RYUJINIII_START_UPLOAD_COMMAND_H
#define RYUJINIII_START_UPLOAD_COMMAND_H

#include <memory>
#include "base_command.h"

/**
 * Command to notify the starting of a upload
 */
class StartUploadCommand : public BaseCommand {
public:
    /**
     * Constructor which sets the wrapper property
     * @param wrapper Reference to libusb wrapper
     */
    StartUploadCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);

    /**
     * Default execution command
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default command instruction
     */
    const unsigned char kStartUpload[3] = {0xec, 0x73, 0x01};
    /**
     * Default instruction to validate the response
     */
    const unsigned char kValidateResponse[2] = {0xec, 0x73};
};

#endif // RYUJINIII_START_UPLOAD_COMMAND_H
