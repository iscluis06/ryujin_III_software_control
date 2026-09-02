#ifndef RYUJINIII_LIBUSB_WRAPP_H
#define RYUJINIII_LIBUSB_WRAPP_H

#include <libusb-1.0/libusb.h>
#include <memory>
#include <vector>

/**
 * Wrapper class for libusb, this for testing purposes using google test.
 */
class LibUsbWrapp {
public:
  /**
   * Constructor for wrapper
   * @param handle Reference to device handler
   * @param default_time_out Default timeout for all usb instructions
   */
  LibUsbWrapp(std::shared_ptr<libusb_device_handle *> handle,
              int default_time_out);

  /**
   * Wrapper for interrupt command
   * @param endpoint Endpoint where to send interrupt
   * @param data Data to send through endpoint
   * @return True on success otherwise false
   */
  bool SendInterrupt(unsigned char endpoint,
                     std::vector<unsigned char> &data) const;
  /**
   * Wrapper for control command
   * @param request_type Type of request to send
   * @param request Control request
   * @param value Value to set
   * @param index Index
   * @param buffer Data to send
   * @param length Length of data
   * @return
   */
  bool SendControl(uint8_t request_type, uint8_t request, uint16_t value,
                   uint16_t index, std::vector<unsigned char> &buffer,
                   uint16_t length) const;

  /**
   * Wrapper for bulk command
   * @param endpoint Device endpoint where to send data
   * @param data Data to send
   * @return Returns true if succeed, otherwise false
   */
  bool SendBulk(unsigned char endpoint, std::vector<unsigned char> &data) const;

  /**
   * Helper function which pads enough data (0's) to create an array of desired
   * size.\nUsed to comply with the data size of usb operations.
   * @param array Current data
   * @param array_size Current data length
   * @param desired_size Desired data length for array
   * @return
   */
  static std::vector<unsigned char> FillArray(const unsigned char *array,
                                              int array_size, int desired_size);

private:
  /**
   * Shared pointer to the device handler (ryujin)
   */
  std::shared_ptr<libusb_device_handle *> handle_;
  /**
   * Default timeout for the usb operations.
   */
  int default_time_out_;
};

#endif // RYUJINIII_LIBUSB_WRAPP_H
