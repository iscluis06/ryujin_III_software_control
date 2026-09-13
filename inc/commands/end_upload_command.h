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
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kEndUpload = {0xec, 0x73, 0xff};
    /**
     * Default instruction to validate against the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x73};
};

#endif // RYUJINIII_END_UPLOAD_COMMAND_H
