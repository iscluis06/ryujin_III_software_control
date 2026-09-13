#ifndef RYUJINIII_RYUJIN_FAN_SPEED_LINE_H
#define RYUJINIII_RYUJIN_FAN_SPEED_LINE_H

#include "led_line/led_line_base.h"
#include "led_line/ryujin_status_line.h"

class RyujinFanSpeedLine : public LedLineBase, public RyujinStatusLine {
public:
    RyujinFanSpeedLine(std::shared_ptr<HardwareStatusStore> store);
    ~RyujinFanSpeedLine() override = default;
    std::string GetLine() override;
    std::string GetTitle() override;
};

#endif // RYUJINIII_RYUJIN_FAN_SPEED_LINE_H
