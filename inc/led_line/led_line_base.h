#ifndef RYUJINIII_LED_LINE_BASE_H
#define RYUJINIII_LED_LINE_BASE_H

#include <string>

class LedLineBase {
public:
    LedLineBase() = default;
    virtual ~LedLineBase() = default;
    virtual std::string GetLine() = 0; // MAX 12
    virtual std::string GetTitle() = 0; // MAX 18
};

#endif // RYUJINIII_LED_LINE_BASE_H
