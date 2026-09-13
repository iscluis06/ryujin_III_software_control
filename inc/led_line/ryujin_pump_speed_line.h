#ifndef RYUJINIII_RYUJIN_PUMP_SPEED_LINE_H
#define RYUJINIII_RYUJIN_PUMP_SPEED_LINE_H

#include "led_line/led_line_base.h"
#include "led_line/ryujin_status_line.h"

class RyujinPumpSpeedLine : public LedLineBase, public RyujinStatusLine {
public:
    RyujinPumpSpeedLine(std::shared_ptr<HardwareStatusStore> store);
    ~RyujinPumpSpeedLine() override = default;
    std::string GetLine() override;
    std::string GetTitle() override;
};

#endif // RYUJINIII_RYUJIN_PUMP_SPEED_LINE_H
