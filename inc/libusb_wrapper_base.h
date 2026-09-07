#ifndef RYUJINIII_LIBUSB_WRAPPER_BASE_H
#define RYUJINIII_LIBUSB_WRAPPER_BASE_H

#include <cstdint>
#include <vector>

/**
 * Wrapper class for libusb, this for testing purposes using google test.
 */
class LibUsbWrapperBase {
public:
    /**
     * Constructor for wrapper
     */
    LibUsbWrapperBase() = default;

    /**
     * Destructor
     */
    virtual ~LibUsbWrapperBase() = default;

    /**
     * Wrapper for interrupt command
     * @param endpoint Endpoint where to send interrupt
     * @param data Data to send through endpoint
     * @return True on success otherwise false
     */
    virtual bool SendInterrupt(unsigned char endpoint, std::vector<unsigned char> &data) const = 0;
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
    virtual bool SendControl(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index,
                             std::vector<unsigned char> &buffer, uint16_t length) const = 0;

    /**
     * Wrapper for bulk command
     * @param endpoint Device endpoint where to send data
     * @param data Data to send
     * @return Returns true if succeed, otherwise false
     */
    virtual bool SendBulk(unsigned char endpoint, std::vector<unsigned char> &data) const = 0;
    /**
     * Helper function which pads enough data (0's) to create an array of desired
     * size.<br>Used to comply with the data size of usb operations.
     * @param array Current data
     * @param array_size Current data length
     * @param desired_size Desired data length for array
     * @return
     */
    virtual std::vector<unsigned char> FillArray(const unsigned char *array, int array_size, int desired_size);

    /**
     * Method that iterates all usb interfaces looking for a device,
     * if found it will set the device variable and claim interfaces.
     * @return True on success, otherwise false
     */
    [[nodiscard]] virtual bool InitializeDevice(int deviceId, int productId) = 0;

    [[nodiscard]] virtual bool ClaimInterfaces(int interface) const = 0;

    [[nodiscard]] virtual bool HaltEndpoint(int endpoint) const = 0;

    [[nodiscard]] virtual bool ReleaseInterface(int interface) const = 0;
};

#endif // RYUJINIII_LIBUSB_WRAPPER_BASE_H
