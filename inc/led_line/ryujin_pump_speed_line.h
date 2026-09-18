#ifndef RYUJINIII_RYUJIN_PUMP_SPEED_LINE_H
#define RYUJINIII_RYUJIN_PUMP_SPEED_LINE_H

#include "led_line/led_line_base.h"
#include "led_line/ryujin_status_line.h"

/**
 * Class that returns the current pump speed of ryujin hardware
 */
class RyujinPumpSpeedLine : public LedLineBase, public RyujinStatusLine {
public:
    /**
     * Constructor which sets the reference to store property
     * @param store Reference to hardware status store
     */
    RyujinPumpSpeedLine(std::shared_ptr<HardwareStatusStore> store);
    /**
     * Default destructor
     */
    ~RyujinPumpSpeedLine() override = default;
    /**
     * Define a value to be shown led display, maximum 12 characters according to my findings
     * @return The value to shown on second line
     */
    std::string GetLine() override;
    /**
     * Define a label to be shown led display, maximum 18 characters according to my findings
     * @return The value to shown on first line
     */
    std::string GetTitle() override;
    /**
     * Utility method for testing purposes
     * @return The class name
     */
    virtual std::string GetClassName() override;
};

#endif // RYUJINIII_RYUJIN_PUMP_SPEED_LINE_H
