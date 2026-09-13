#ifndef RYUJINIII_RYUJIN_LIQUID_TEMP_LINE_H
#define RYUJINIII_RYUJIN_LIQUID_TEMP_LINE_H
#include "led_line_base.h"
#include "ryujin_status_line.h"

class RyujinLiquidTempLine : public LedLineBase, public RyujinStatusLine {
public:
    RyujinLiquidTempLine(std::shared_ptr<HardwareStatusStore> store);
    ~RyujinLiquidTempLine() override = default;
    std::string GetLine() override;
    std::string GetTitle() override;
};

#endif // RYUJINIII_RYUJIN_LIQUID_TEMP_LINE_H
