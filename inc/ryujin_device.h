#ifndef RYUJINIII_RYUJIN_DEVICE_H
#define RYUJINIII_RYUJIN_DEVICE_H

#include <memory>
#include <thread>

#include "wrappers/libusb_wrapper_base.h"
/**
 * Main class for all ryujin device properties.
 */
class RyujinDevice {
public:
    /**
     * Constructor which uses FindDevice to initialize device property,
     * if device property not initialized (device not found), it will terminate
     * the application with exit code 0.
     */
    RyujinDevice(std::shared_ptr<LibUsbWrapperBase> wrapper);

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
     * Gets a shared ptr to usb handler
     * @return Shared pointer to usb handler
     */
    std::shared_ptr<LibUsbWrapperBase> GetWrapper() { return this->wrapper_; }

private:
    /**
     * Reference to libusb wrapper
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
};

#endif // RYUJINIII_RYUJIN_DEVICE_H
