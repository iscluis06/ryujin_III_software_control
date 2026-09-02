#ifndef RYUJINIII_DEFAULT_GIF_H
#define RYUJINIII_DEFAULT_GIF_H
#include "base_command.h"

/**
 * Command for setting default gif into display
 */
class DefaultGif : public BaseCommand {
public:
  /**
   * Constructor which also sets the reference to device handler
   * @param device Reference to device handler
   */
  DefaultGif(std::shared_ptr<libusb_device_handle *> device);
  /**
   * Default destructor
   */
  ~DefaultGif() override = default;
  /**
   * Method to execute the command
   * @return True on sucess, otherwise false
   */
  bool Execute() override;
  /**
   * Default instruction command
   */
  unsigned char kDefaultGIFInstruction[3] = {0xec, 0x51, 0x14};
};

#endif // RYUJINIII_DEFAULT_GIF_H
