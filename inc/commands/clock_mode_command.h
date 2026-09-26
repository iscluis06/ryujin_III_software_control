#ifndef RYUJINIII_CLOCK_MODE_COMMAND_H
#define RYUJINIII_CLOCK_MODE_COMMAND_H

#include <ctime>
#include "byte_utils.h"
#include "commands/base_command.h"

class ClockModeCommand : public BaseCommand {
public:
    ClockModeCommand(std::shared_ptr<LibUsbWrapperBase> base);
    std::string GetClassName() const override;

private:
    std::time_t current_time_;
    enum class TimePeriod { AM_PERIOD = 0, PM_PERIOD };
    std::vector<unsigned char> kInstruction = {0xec, 0x11, 0xc6, 0x9, 0x23, 0x3, 0x1, 0x3, 0x59, 0x59, 0x0, 0x0, 0x0,
                                               0x0,  0x0,  0x0,  0x0, 0x0,  0x0, 0x0, 0x0, 0x0,  0x0,  0x0, 0x0, 0x0,
                                               0x0,  0x0,  0x0,  0x0, 0x0,  0x0, 0x0, 0x0, 0x0,  0x0,  0x0, 0x0, 0x0,
                                               0x0,  0x0,  0x0,  0x0, 0x0,  0x0, 0x0, 0x0, 0x0,  0x0,  0x0, 0x0, 0x0,
                                               0x0,  0x0,  0x0,  0x0, 0x0,  0x0, 0x0, 0x0, 0x0,  0x0,  0x0, 0x0, 0x0};
    const int kHourIndex = 7;
    const int kMinuteIndex = 8;
    const int kSecondsIndex = 9;
    const int kTimePeriod = 10;
    int GetHourDecimalValue();
    int GetMinuteDecimalValue();
    int GetSecondDecimalValue();
    TimePeriod GetPMOrAM();
    ByteUtils byteutils_;
};

#endif // RYUJINIII_CLOCK_MODE_COMMAND_H
