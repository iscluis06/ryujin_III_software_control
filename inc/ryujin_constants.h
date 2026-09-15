#ifndef RYUJINIII_RYUJIN_CONSTANTS_H
#define RYUJINIII_RYUJIN_CONSTANTS_H

class RyujinConstants {
public:
    /**
     * Config Interface Identifier needed to claim it using libusb.
     */
    static constexpr int kConfigInterface = 0x0;
    /**
     * Led Interface Identifier needed to claim it using libusb.
     */
    static constexpr int kLedInterface = 0x1;
    /**
     * Asus identifier
     */
    static constexpr int kAsusDeviceId = 0x0b05;
    /**
     * Product identifier
     */
    static constexpr int kRyujinProductId = 0x1aa2;
    /**
     * Wrapper reference
     */
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
    /**
     * Default length for usb interrupt instructions.
     */
    static const int kDefaultInterruptDataLength = 65;
    /**
     * Default command for usb bulk instructions.
     */
    static const int kDefaultBulkLength = 4096;
    /**
     * Enum of current mode implementations.
     * TODO: Implement CUSTOM
     */
    enum class MonitorMode : short { GALACTIC, PUNK, CUSTOM };
    /**
     * Enum of all posible background styles
     */
    enum class MonitorStyle : short { STYLE01 = 0x0, STYLE02 = 0x1, STYLE03 = 0x2, STYLE04 = 0x3 };
    /**
     * Enum of all posible line configs, LINES1 will show only one monitor line, LINES2 two lines and so on
     */
    enum class LinesConfig : short { LINES1 = 0x0, LINES2 = 0x1, LINES3 = 0x2 };
};

#endif // RYUJINIII_RYUJIN_CONSTANTS_H
