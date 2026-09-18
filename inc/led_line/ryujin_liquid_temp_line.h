#ifndef RYUJINIII_RYUJIN_LIQUID_TEMP_LINE_H
#define RYUJINIII_RYUJIN_LIQUID_TEMP_LINE_H
#include "led_line_base.h"
#include "ryujin_status_line.h"

/**
 * Class that returns the current liquid temperature of ryujin hardware
 */
class RyujinLiquidTempLine : public LedLineBase, public RyujinStatusLine {
public:
    /**
     * Constructor which sets the reference to store property
     * @param store Reference to hardware status store
     */
    RyujinLiquidTempLine(std::shared_ptr<HardwareStatusStore> store);
    /**
     * Default destructor
     */
    ~RyujinLiquidTempLine() override = default;
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

#endif // RYUJINIII_RYUJIN_LIQUID_TEMP_LINE_H
