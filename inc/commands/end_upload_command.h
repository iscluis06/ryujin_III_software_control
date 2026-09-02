#ifndef RYUJINIII_END_UPLOAD_COMMAND_H
#define RYUJINIII_END_UPLOAD_COMMAND_H

#include "base_command.h"
#include <libusb-1.0/libusb.h>
#include <memory>

/**
 * Command to execute end of upload
 */
class EndUploadCommand : public BaseCommand {
public:
  /**
   * Constructor which also sets device handler property
   * @param device Reference to device handler
   */
  EndUploadCommand(std::shared_ptr<libusb_device_handle *> device);

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
