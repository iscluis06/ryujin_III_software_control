#ifndef RYUJINIII_END_UPLOAD_COMMAND_H
#define RYUJINIII_END_UPLOAD_COMMAND_H

#include <memory>
#include "base_command.h"

/**
 * Command to execute end of upload
 */
class EndUploadCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets the reference to wrapper
     * @param wrapper Reference to libusb wrapper
     */
    EndUploadCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);

    /**
     * Default execution of command
     * @return True on succeed, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default command instruction
     */
    const unsigned char kEndUpload[3] = {0xec, 0x73, 0xff};
    /**
     * Default instruction to validate against the response
     */
    const unsigned char kValidateResponse[2] = {0xec, 0x73};
};

#endif // RYUJINIII_END_UPLOAD_COMMAND_H
