#include "date_utils.h"

#include <chrono>

std::string DateUtils::GetFullTimeStamp() {
    auto now = std::chrono::system_clock::now();
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto fraction = now - seconds;
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction).count();
    char time[kFullTimeStampLength + kNullCharacterLength];
    strftime(time, kFullTimeStampLength + kNullCharacterLength, "%Y%m%d%H%M%S", std::localtime(&time_now));
    snprintf(&time[kTimeStampLength], kMillisecondsLength + kNullCharacterLength, "%ld", milliseconds);
    return time;
}
