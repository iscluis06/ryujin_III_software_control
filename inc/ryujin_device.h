#ifndef RYUJINIII_RYUJIN_DEVICE_H
#define RYUJINIII_RYUJIN_DEVICE_H

#include <libusb-1.0/libusb.h>
#include <memory>
#include <string>

#include "libusb_wrapp.h"
/**
 * Main class for all ryujin device properties.
 */
class RyujinDevice {
private:
  /**
   * Config Interface Identifier needed to claim it using libusb.
   */
  const int kConfigInterface = 0x0;
  /**
   * Led Interface Identifier needed to claim it using libusb.
   */
  const int kLedInterface = 0x1;
  /**
   * Asus identifier
   */
  const int kAsusDeviceId = 0x0b05;
  /**
   * Product identifier
   */
  const int kRyujinProductId = 0x1aa2;
  /**
   * Shared pointer to the device handle
   */
  std::shared_ptr<libusb_device_handle *> device;

  /**
   * Method that iterates all usb interfaces looking for ryujin device,
   * if found it will set the device variable.
   */
  void FindDevice();

public:
  /**
   * Constructor which uses FindDevice to initialize device property,
   * if device property not initialized (device not found), it will terminate
   * the application with exit code 0.
   */
  RyujinDevice();

  /**
   * Destructor releases usb interfaces previously claimed.
   */
  ~RyujinDevice();

  /**
   * Method executes turn on command.
   */
  void TurnOnLedDisplay() const;

  /**
   * Method executes turn off command.
   */
  void TurnOffLedDisplay() const;

  void SelectGifFromMemory(int memory_index) const;

  /**
   * Method executes delete command. (only gif spaces)
   */
  void DeleteFromMemory(int memory_index) const;

  /**
   * Method executes upload gif command
   * @param path To gif file
   * @param memory_space Memory slot where to upload gif (1-10)
   */
  void UploadGif(const std::string &path, short memory_space);

  /**
   * Default length for usb interrupt instructions.
   */
  static const int kDefaultInterruptDataLength = 65;
  /**
   * Default command for usb bulk instructions.
   */
  static const int kDefaultBulkLength = 4096;

  /**
   * Gets a shared ptr to usb handler
   * @return Shared pointer to usb handler
   */
  std::shared_ptr<libusb_device_handle *> GetDeviceHandle() {
    return this->device;
  }

  /**
   * USB device output endpoint
   */
  static const int kVendorDeviceOut = 0x01;
  /**
   * USB device input endpoint
   */
  static const int kVendorDeviceIn = 0x81;
  /**
   * USB device bulk output endpoint
   */
  static const int kHidDeviceOut = 0x02;
  /**
   * USB device bulk input endpoint
   */
  static const int kHidDeviceIn = 0x82;
};

#endif // RYUJINIII_RYUJIN_DEVICE_H
