#ifndef RYUJINIII_LIBUSB_WRAPPER_MOCK_H
#define RYUJINIII_LIBUSB_WRAPPER_MOCK_H

#include <gmock/gmock.h>

#include "libusb_wrapper_base.h"

class LibUsbWrapperMock : public LibUsbWrapperBase {
public:
    MOCK_METHOD(bool, SendInterrupt, (unsigned char endpoint, std::vector<unsigned char> &data), (const, override));
    MOCK_METHOD(bool, SendControl,
                (uint8_t request_type, uint8_t request, uint16_t value, uint16_t index,
                 std::vector<unsigned char> &buffer, uint16_t length),
                (const, override));
    MOCK_METHOD(bool, SendBulk, (unsigned char endpoint, std::vector<unsigned char> &data), (const, override));
    MOCK_METHOD(std::vector<unsigned char>, FillArray, (const unsigned char *array, int array_size, int desired_size),
                (override));
    MOCK_METHOD(bool, InitializeDevice, (int deviceId, int productId), (override));
    MOCK_METHOD(bool, ClaimInterfaces, (int interface), (const, override));
    MOCK_METHOD(bool, HaltEndpoint, (int endpoint), (const, override));
    MOCK_METHOD(bool, ReleaseInterface, (int interface), (const, override));
};

#endif // RYUJINIII_LIBUSB_WRAPPER_MOCK_H
