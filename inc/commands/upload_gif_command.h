#ifndef RYUJINIII_UPLOAD_GIF_COMMAND_H
#define RYUJINIII_UPLOAD_GIF_COMMAND_H

#include "base_command.h"
#include <libusb-1.0/libusb.h>
#include <memory>

#include "file_handle.h"

/**
 * Command to upload a gif file
 */
class UploadGifCommand : public BaseCommand {
public:
  /**
   * Constructor which sets the device and file handle properties
   * @param device Reference to device handle
   * @param file_handle Reference to file handle
   */
  UploadGifCommand(std::shared_ptr<libusb_device_handle *> device,
                   const FileHandle &file_handle);

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
  const FileHandle &file_handle;
};

#endif // RYUJINIII_UPLOAD_GIF_COMMAND_H
