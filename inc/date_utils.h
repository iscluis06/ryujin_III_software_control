#ifndef RYUJINIII_DATE_UTILS_H
#define RYUJINIII_DATE_UTILS_H

#include <string>

class DateUtils {
public:
    static std::string GetFullTimeStamp();

private:
    static constexpr int kNullCharacterLength = 1;
    static constexpr int kTimeStampLength = 14;
    static constexpr int kFullTimeStampLength = 17;
    static constexpr int kMillisecondsLength = 3;
};

#endif // RYUJINIII_DATE_UTILS_H
