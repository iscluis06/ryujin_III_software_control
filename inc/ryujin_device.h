#ifndef RYUJINIII_RYUJIN_DEVICE_H
#define RYUJINIII_RYUJIN_DEVICE_H

#include <libusb-1.0/libusb.h>
#include <string>
#include <memory>

#include "libusb_wrapp.h"

class RyujinDevice {
private:
    std::unique_ptr<LibUsbWrapp> lusb_;

    class FileHandle {
    public:
        std::shared_ptr<unsigned char[]> buffer;
        int size;
    };

    const int kConfigInterface = 0x0;
    const int kLedInterface = 0x1;
    const int kAsusDeviceId = 0x0b05;
    const int kRyujinProductId = 0x1aa2;
    const int kDefaultTimeOut = 5000;

    std::shared_ptr<libusb_device_handle *> device;

    void GetDevice();

public:
    RyujinDevice();

    ~RyujinDevice();

    void Reset() const;

    void TurnOnLedDisplay() const;

    void TurnOffLedDisplay() const;

    void SelectGifFromMemory(int memory_index) const;

    void DeleteFromMemory(int memory_index) const;

    void UploadGif(const std::string &path, short memory_space);

    // Default lengths
    static const int kDefaultInterruptDataLength = 65;
    static const int kDefaultBulkLength = 4096;


    // Endpoints
    static const int kVendorDeviceOut = 0x01;
    static const int kVendorDeviceIn = 0x81;
    static const int kHidDeviceOut = 0x02;
    static const int kHidDeviceIn = 0x82;
};

#endif //RYUJINIII_RYUJIN_DEVICE_H
