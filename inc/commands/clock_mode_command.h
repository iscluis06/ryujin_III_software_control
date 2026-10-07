#ifndef RYUJINIII_CLOCK_MODE_COMMAND_H
#define RYUJINIII_CLOCK_MODE_COMMAND_H

#include <ctime>
#include "byte_utils.h"
#include "commands/base_command.h"

/**
 * Command to activate the clock mode
 */
class ClockModeCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     */
    ClockModeCommand(std::shared_ptr<LibUsbWrapperBase> base);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Object for current time, in order to set the clock time on ryujin display
     */
    std::time_t current_time_;
    /**
     * Enum for AM or PM time
     */
    enum class TimePeriod { AM_PERIOD = 0, PM_PERIOD };
    /**
     * Default command instruction
     */
    std::vector<unsigned char> kInstruction = {0xec, 0x11, 0xc6, 0x9, 0x23, 0x3, 0x1, 0x3, 0x59, 0x59};
    /**
     * Hour index for instruction
     */
    const int kHourIndex = 7;
    /**
     * Minute index for instruction
     */
    const int kMinuteIndex = 8;
    /**
     * Second index for instruction
     */
    const int kSecondsIndex = 9;
    /**
     * Period (AM/PM) index for instruction
     */
    const int kTimePeriod = 10;
    /**
     * Returns the hours as a decimal value
     * @return Decimal value for hour
     */
    int GetHourDecimalValue();
    /**
     * Returns the minutes as a decimal value
     * @return Decimal value for minute
     */
    int GetMinuteDecimalValue();
    /**
     * Returns the seconds as a decimal value
     * @return Decimal value for seconds
     */
    int GetSecondDecimalValue();
    /**
     * Evaluates the current local time of the machine and determines the period (AM|PM)
     * @return The period according to the local time of the machine
     */
    TimePeriod GetPMOrAM();
    /**
     * ByteUtils instance
     */
    ByteUtils byteutils_;
};

#endif // RYUJINIII_CLOCK_MODE_COMMAND_H
