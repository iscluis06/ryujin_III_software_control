#ifndef RYUJINIII_START_UPLOAD_COMMAND_H
#define RYUJINIII_START_UPLOAD_COMMAND_H

#include "base_command.h"
#include <libusb-1.0/libusb.h>
#include <memory>

/**
 * Command to notify the starting of a upload
 */
class StartUploadCommand : public BaseCommand {
public:
  /**
   * Constructor which sets the device property
   * @param device Reference to device handler
   */
  StartUploadCommand(std::shared_ptr<libusb_device_handle *> device);

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
