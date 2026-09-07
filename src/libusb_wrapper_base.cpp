#include "libusb_wrapper_base.h"
#include <cstring>

std::vector<unsigned char> LibUsbWrapperBase::FillArray(const unsigned char *array, int array_size, int desired_size) {
    std::vector<unsigned char> buffer(desired_size, 0);
    memcpy(buffer.data(), array, array_size);
    return buffer;
}
