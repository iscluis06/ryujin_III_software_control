#ifndef RYUJINIII_RYUJIN_FAN_SPEED_LINE_H
#define RYUJINIII_RYUJIN_FAN_SPEED_LINE_H

#include "led_line/led_line_base.h"
#include "led_line/ryujin_status_line.h"

/**
 * Class that returns the current fan speed of ryujin hardware
 */
class RyujinFanSpeedLine : public LedLineBase, public RyujinStatusLine {
public:
    /**
     * Constructor which sets the reference to store property
     * @param store Reference to hardware status store
     */
    RyujinFanSpeedLine(std::shared_ptr<HardwareStatusStore> store);
    /**
     * Default destructor
     */
    ~RyujinFanSpeedLine() override = default;
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

#endif // RYUJINIII_RYUJIN_FAN_SPEED_LINE_H
