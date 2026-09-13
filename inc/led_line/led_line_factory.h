#ifndef RYUJINIII_LED_LINE_FACTORY_H
#define RYUJINIII_LED_LINE_FACTORY_H

#include <memory>
#include "led_line/led_line_base.h"
#include "stores/hardware_status_store.h"

class LedLineFactory {
public:
    enum class LedLineImplementations {
        RYUJIN_LIQUID_TEMP = 0,
        RYUJIN_PUMP_SPEED,
        RYUJIN_FAN_SPEED,
        AMD_CORE_TEMP,
        GIT_LAST_COMMITER
    };
    LedLineFactory(std::shared_ptr<HardwareStatusStore> store);
    std::shared_ptr<LedLineBase> GetLedLine(LedLineImplementations implementation);
    void SetGitPath(std::string path);
    static std::string PrintCurrentImplements();

private:
    std::shared_ptr<HardwareStatusStore> store_;
    std::string git_path_;
};

#endif // RYUJINIII_LED_LINE_FACTORY_H
