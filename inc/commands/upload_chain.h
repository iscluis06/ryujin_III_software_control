#ifndef RYUJINIII_UPLOAD_CHAIN_H
#define RYUJINIII_UPLOAD_CHAIN_H

#include "command_chain.h"
#include "file_handle.h"

/**
 * Command chain to upload a gif file
 */
class UploadChain : public CommandChain {
public:
  /**
   * Constructor which sets all required command properties
   * @param device Reference to device handler
   * @param path Path to the gif file to upload
   * @param memory_index Memory space where to upload gif
   */
  UploadChain(std::shared_ptr<libusb_device_handle *> device,
              const std::string &path, int memory_index);

  /**
   * Execution of chain commands
   * @return True on success, otherwise false
   */
  bool Execute() override;

private:
  /**
   * File handle
   */
  FileHandle file_handle_;
  /**
   * Max number of tries before canceling command
   */
  const int kMaxTries_ = 3;
  /**
   * Default path to save processed gif file
   */
  static const std::string kFinalGifPath_;
};

#endif // RYUJINIII_UPLOAD_CHAIN_H
