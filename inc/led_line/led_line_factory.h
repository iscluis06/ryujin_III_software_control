#ifndef RYUJINIII_LED_LINE_FACTORY_H
#define RYUJINIII_LED_LINE_FACTORY_H

#include <memory>
#include "led_line/led_line_base.h"
#include "stores/hardware_status_store.h"

/**
 * Factory to create led line implementations
 */
class LedLineFactory {
public:
    /**
     * Enum that contains all implements
     */
    enum class LedLineImplementations {
        RYUJIN_LIQUID_TEMP = 0,
        RYUJIN_PUMP_SPEED,
        RYUJIN_FAN_SPEED,
        AMD_CORE_TEMP,
        GIT_LAST_COMMITER
    };
    /**
     * Constructor which sets the store property
     * @param store Hardware status store, used to avoid multiple by request by all
     * ryujin sensor requests.
     */
    LedLineFactory(std::shared_ptr<HardwareStatusStore> store);
    /**
     * Factory method to create a LedLineBase instance
     * @param implementation Led implementation to create
     * @return A reference to the created instance, if fail then returns nullptr
     */
    std::shared_ptr<LedLineBase> GetLedLine(LedLineImplementations implementation);
    /**
     * Helper method to set the git path for git last commiter implementation
     * @param path Path to local git repository
     */
    void SetGitPath(std::string path);
    /**
     * Print all implementations currently defined
     * @return A string with all implementations defined
     */
    static std::string PrintCurrentImplements();

private:
    /**
     * Reference to hardware status store
     */
    std::shared_ptr<HardwareStatusStore> store_;
    /**
     * Property that holds the path to the local git repo
     */
    std::string git_path_;
};

#endif // RYUJINIII_LED_LINE_FACTORY_H
