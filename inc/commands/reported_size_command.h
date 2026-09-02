#ifndef RYUJINIII_REPORTED_SIZE_COMMAND_H
#define RYUJINIII_REPORTED_SIZE_COMMAND_H

#include "base_command.h"
#include <libusb-1.0/libusb.h>
#include <memory>

/**
 * Command to report the size of the uploading file
 */
class ReportedSizeCommand : public BaseCommand {
public:
  /**
   * Constructor which also sets device and size properties
   * @param device Reference to device handler
   * @param size Size of the file to upload on little endian format
   */
  ReportedSizeCommand(std::shared_ptr<libusb_device_handle *> device,
                      std::vector<unsigned char> size);

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
