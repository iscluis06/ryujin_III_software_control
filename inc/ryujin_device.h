#ifndef RYUJINIII_RYUJIN_DEVICE_H
#define RYUJINIII_RYUJIN_DEVICE_H

#include <libusb-1.0/libusb.h>
#include <memory>
#include <string>
#include "libusb_wrapper.h"
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
     * Wrapper reference
     */
    std::shared_ptr<LibUsbWrapper> wrapper_;

public:
    /**
     * Constructor which uses FindDevice to initialize device property,
     * if device property not initialized (device not found), it will terminate
     * the application with exit code 0.
     */
    RyujinDevice(std::shared_ptr<LibUsbWrapper> wrapper);

    /**
     * Destructor releases usb interfaces previously claimed.
     */
    ~RyujinDevice();

    /**
     * Initializer routine, it searches for the device and start libusb claiming interface
     * @return True on success, otherwise false
     */
    bool Initialize();

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
    std::shared_ptr<LibUsbWrapper> GetWrapper() { return this->wrapper_; }

    /**
     * USB device output endpoint
     */
    static constexpr int kVendorDeviceOut = 0x01;
    /**
     * USB device input endpoint
     */
    static constexpr int kVendorDeviceIn = 0x81;
    /**
     * USB device bulk output endpoint
     */
    static constexpr int kHidDeviceOut = 0x02;
    /**
     * USB device bulk input endpoint
     */
    static constexpr int kHidDeviceIn = 0x82;
    /**
     * Global default timeout on milliseconds
     */
    static constexpr int kDefaultTimeout = 5000;
};

#endif // RYUJINIII_RYUJIN_DEVICE_H
