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
    const int kVendorDeviceOut = 0x01;
    const int kHidDeviceOut = 0x02;
    const int kDefaultTimeOut = 500;
    const int kDefaultInterruptDataLength = 65;
    const unsigned char kTurnOff[2] = {0xec, 0x51};
    const unsigned char kTurnOn[3] = {0xec, 0x51, 0x14};
    const unsigned char kSelectGif[4] = {0xec, 0x51, 0x10, 0x01};
    const unsigned char kSelectMemory[4] = {0xec, 0x72, 0x01, 0x02};
    const unsigned char kTransaction[4] = {0xec, 0x71, 0x01, 0x01};
    const unsigned char kStartTransaction[2] = {0xec, 0xf1};
    const unsigned char kStartUpload[3] = {0xec, 0x73, 0x01};
    const unsigned char kInterruptUpload[5] = {0xee, 0x14, 0x0, 0x0, 0x10};
    const unsigned char kReportedSize[3] = {0xec, 0x7f, 0x02};
    const unsigned char kEndUpload[3] = {0xec, 0x73, 0xff};
    const unsigned char kEndUpload2[3] = {0xec, 0xdc};
    const unsigned char kDelete[3] = {0xec, 0x73, 0x03};
    const unsigned char kReportHid[5] = {0xec, 0x1a, 0x01, 0x14, 0x1e};
    std::shared_ptr<libusb_device_handle *> device;

    void GetDevice();
    std::vector<unsigned char> FillArray(const unsigned char * array, int array_size, int desired_size);
    std::array<unsigned char, 3> GetSizeToHex(int size);
    std::shared_ptr<FileHandle> ReadFile(std::string path);
public:
    RyujinDevice();
    ~RyujinDevice();
    void Reset();
    void TurnOnLedDisplay();
    void TurnOffLedDisplay();
    void SelectGifFromMemory(int memory_index);
    void DeleteFromMemory(int memory_index);
    void UploadGif(std::string path);
};

#endif //RYUJINIII_RYUJIN_DEVICE_H
