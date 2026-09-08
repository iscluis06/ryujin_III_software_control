#ifndef RYUJINIII_LIBUSB_WRAPPER_H
#define RYUJINIII_LIBUSB_WRAPPER_H

#include <libusb-1.0/libusb.h>
#include <memory>

#include "libusb_wrapper_base.h"

/**
 * Default implement for libusb wrapper
 */
class LibUsbWrapper : public LibUsbWrapperBase {
public:
    /**
     * Constructor for wrapper
     */
    LibUsbWrapper();

    /**
     * Destructor
     */
    ~LibUsbWrapper() override;

    /**
     * Wrapper for interrupt command
     * @param endpoint Endpoint where to send interrupt
     * @param data Data to send through endpoint
     * @return True on success otherwise false
     */
    bool SendInterrupt(unsigned char endpoint, std::vector<unsigned char> &data) const override;
    /**
     * Wrapper for control command
     * @param request_type Type of request to send
     * @param request Control request
     * @param value Value to set
     * @param index Index
     * @param buffer Data to send
     * @param length Length of data
     * @return True on success, otherwise false
     */
    bool SendControl(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index,
                     std::vector<unsigned char> &buffer, uint16_t length) const override;
    /**
     * Wrapper for bulk command
     * @param endpoint Device endpoint where to send data
     * @param data Data to send
     * @return Returns true if succeed, otherwise false
     */
    bool SendBulk(unsigned char endpoint, std::vector<unsigned char> &data) const override;
    /**
     * Set the timeout for all operations
     * @param timeout Default timeout to set
     */
    void SetTimeout(int timeout);
    /**
     * Set the device handler reference
     * @param handle Reference to the device handler
     */
    void SetHandle(std::shared_ptr<libusb_device_handle *> handle);
    /**
     * Method that iterates all usb interfaces looking for a device,
     * if found it will set the device variable and claim interfaces.
     * @return True on success, otherwise false
     */
    [[nodiscard]] bool InitializeDevice(int deviceId, int productId) override;
    /**
     * Method to claim usb interfaces
     * @param interface Interface id to claim
     * @return Returns true on success, otherwise false
     */
    [[nodiscard]] bool ClaimInterfaces(int interface) const override;
    /**
     * Halts/Clean an endpoint
     * @param endpoint Endpoint id to halt
     * @return True on success, otherwise false
     */
    [[nodiscard]] bool HaltEndpoint(int endpoint) const override;
    /**
     * Release a usb interface by id
     * @param interface Interface id to release
     * @return True on success, otherwise false
     */
    [[nodiscard]] bool ReleaseInterface(int interface) const override;

private:
    /**
     * Shared pointer to the device handler (ryujin)
     */
    std::shared_ptr<libusb_device_handle *> handle_;
    /**
     * Default timeout for the usb operations.
     */
    int default_time_out_ = 0;
};

#endif // RYUJINIII_LIBUSB_WRAPPER_H
