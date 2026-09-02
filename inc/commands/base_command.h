#ifndef RYUJINIII_BASE_COMMAND_H
#define RYUJINIII_BASE_COMMAND_H

#include <libusb-1.0/libusb.h>
#include <memory>
#include <vector>
/**
 * Abstract class for testing purposes
 */
class BaseCommand {
public:
  /**
   * Constructor for base command class
   * @param device Reference to device usb handler
   */
  BaseCommand(std::shared_ptr<libusb_device_handle *> device);

  /**
   * Constructor which also sets validation options
   * @param device Reference to device usb handler
   * @param valid_message_back Default validation for response
   * @param valid_message_back_size Default size validation for response
   */
  BaseCommand(std::shared_ptr<libusb_device_handle *> device,
              const unsigned char *valid_message_back,
              int valid_message_back_size);
  /**
   * Virtual destructor for abstraction
   */
  virtual ~BaseCommand() = default;

  /**
   * Default method to execute command
   * @return True on success, otherwise false
   */
  virtual bool Execute() = 0;

  /**
   *  Method to validate message argument
   * @param message Validates if given message is valid, it compares against
   * valid_message_back and valid_message_back_size properties
   * @return True if validation pass, otherwise false
   */
  bool IsMessageValid(const std::vector<unsigned char> &message) const;

  /**
   * Getter for device handler reference
   * @return Reference to device handle
   */
  std::shared_ptr<libusb_device_handle *> GetDevice() const;

  /**
   * Default timeout for command
   */
  const int kTimeout = 1000;

private:
  /**
   * Device handler reference
   */
  std::shared_ptr<libusb_device_handle *> device_;
  /**
   * Message to validate against a response
   */
  const unsigned char *valid_message_back_ = nullptr;
  /**
   * Size of response to validate against
   */
  int valid_message_back_size_ = 0;
};

#endif // RYUJINIII_BASE_COMMAND_H
