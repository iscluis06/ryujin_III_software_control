#ifndef RYUJINIII_HARDWARE_MONITOR_CONFIG_H
#define RYUJINIII_HARDWARE_MONITOR_CONFIG_H
#include <vector>
#include "hardware_monitor_chain.h"
#include "led_line/led_line_factory.h"
#include "ryujin_constants.h"

/**
 * Helper class to configure hardware monitor chain command
 */
class HardwareMonitorChainConfig {
public:
    /**
     * Default constructor for hardware monitor chain config class
     * @param wrapper Reference to libusb wrapper
     */
    HardwareMonitorChainConfig(std::shared_ptr<LibUsbWrapperBase> wrapper);
    /**
     * Add a line implementation to show on led display
     * @param line Line implementation to show on led display
     */
    void AddLine(int line);
    /**
     * Sets the mode to show on led display
     * @param mode Mode to show on led display
     */
    void SetMode(int mode);
    /**
     * Configures the background style to show on led display
     * @param style Background style to show
     */
    void SetStyle(int style);
    /**
     * Utility method to configure the path to a git repository for git led line implementation
     * @param git_path Path to git repository
     */
    void SetGitPath(const std::string &git_path);
    /**
     * Returns the configure reference to the hardware monitor chain
     * @return The configured hardware monitor chain
     */
    std::unique_ptr<HardwareMonitorChain> GetChain();

private:
    /**
     * List of selected led line implementations to show on led screen
     */
    std::vector<LedLineFactory::LedLineImplementations> lines_;
    /**
     * Default config for mode to display on hardware monitor, currently CYBERPUNK
     */
    RyujinConstants::MonitorMode mode_ = RyujinConstants::MonitorMode::PUNK;
    /**
     * Default config for background style to show on display, currently STYLE01 = 0x0
     */
    RyujinConstants::MonitorStyle style_ = RyujinConstants::MonitorStyle::STYLE01;
    /**
     * Reference to libusb wrapper
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
    /**
     * Property used to configure git led line implementations
     */
    std::string git_path_;
};

#endif // RYUJINIII_HARDWARE_MONITOR_CONFIG_H
