#ifndef RYUJINIII_LED_LINE_BASE_H
#define RYUJINIII_LED_LINE_BASE_H

#include <string>

/**
 * Helper class to define a value and label to show on led display
 */
class LedLineBase {
public:
    /**
     * Default constructor
     */
    LedLineBase() = default;
    /**
     * Default destructor
     */
    virtual ~LedLineBase() = default;
    /**
     * Define a value to be shown led display, maximum 12 characters according to my findings
     * @return The value to shown on second line
     */
    virtual std::string GetLine() = 0;
    /**
     * Define a label to be shown led display, maximum 18 characters according to my findings
     * @return The value to shown on first line
     */
    virtual std::string GetTitle() = 0;
};

#endif // RYUJINIII_LED_LINE_BASE_H
