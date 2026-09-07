#ifndef RYUJINIII_REPORTED_SIZE_COMMAND_H
#define RYUJINIII_REPORTED_SIZE_COMMAND_H

#include <memory>
#include "base_command.h"

/**
 * Command to report the size of the uploading file
 */
class ReportedSizeCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets wrapper and size properties
     * @param wrapper Reference to libusb wrapper
     * @param size Size of the file to upload on little endian format
     */
    ReportedSizeCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, std::vector<unsigned char> size);

    /**
     * Default execution of command
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default command instruction
     */
    const unsigned char kReportedSize[3] = {0xec, 0x7f, 0x02};
    /**
     * Default instruction to validate the response
     */
    const unsigned char kValidateResponse[5] = {0xec, 0x7f, 0x0, 0x0, 0x10};
    /**
     * Size of the file to upload, on little endian format.
     */
    std::vector<unsigned char> size_;
};

#endif // RYUJINIII_REPORTED_SIZE_COMMAND_H
