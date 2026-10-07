#ifndef RYUJINIII_DATE_UTILS_H
#define RYUJINIII_DATE_UTILS_H

#include <string>

/**
 * Date utility class
 */
class DateUtils {
public:
    /**
     * Method to obtain a full timestamp without spaces
     * @return A string of the current date with the following format %Year%month%day%Hour%Minutes%Seconds%Milliseconds
     */
    static std::string GetFullTimeStamp();

private:
    /**
     * Helper property to specify length of null character
     */
    static constexpr int kNullCharacterLength = 1;
    /**
     * Helper property to specify length of timestamp without milliseconds
     */
    static constexpr int kTimeStampLength = 14;
    /**
     * Helper property to specify length of timestamp with milliseconds
     */
    static constexpr int kFullTimeStampLength = 17;
    /**
     * Helper property to specify length of milliseconds
     */
    static constexpr int kMillisecondsLength = 3;
};

#endif // RYUJINIII_DATE_UTILS_H
