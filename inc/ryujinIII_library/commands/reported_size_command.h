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
    ReportedSizeCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, const std::vector<unsigned char> &size);

    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kReportedSize = {0xec, 0x7f, 0x02};
    /**
     * Default instruction to validate the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x7f, 0x0, 0x0, 0x10};
};

#endif // RYUJINIII_REPORTED_SIZE_COMMAND_H
