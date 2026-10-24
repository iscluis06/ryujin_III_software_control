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
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kStartUpload = {0xec, 0x73, 0x01};
    /**
     * Default instruction to validate the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x73};
};

#endif // RYUJINIII_START_UPLOAD_COMMAND_H
