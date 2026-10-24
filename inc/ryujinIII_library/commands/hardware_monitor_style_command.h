#ifndef RYUJINIII_HARDWARE_MONITOR_STYLE_COMMAND_H
#define RYUJINIII_HARDWARE_MONITOR_STYLE_COMMAND_H

#include <vector>
#include "commands/base_command.h"

/**
 * Command to select the hardware monitor style
 * Based on: https://github.com/BrandonKynoch/asus-rog-ryujin-iii-linux-controller
 * Thanks to BrandonKynoch for his findings
 */
class HardwareMonitorStyleCommand : public BaseCommand {
public:
    /**
     * Command instruction to configure the mode of hardware monitor, lines and background
     * @param wrapper Reference to libusb wrapper
     * @param lines Number of lines to display on led screen
     * @param mode Mode to activate for hardware monitor
     * @param style Background style to show, valid indexes 0x0 to 0x3
     */
    HardwareMonitorStyleCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, int lines, int mode, int style);
    /**
     * Returns the class name for testing purposes
     * @return the name of the class
     */
    std::string GetClassName() const override;

private:
    /**
     * Offset for mode index config
     */
    const short kModeByteOffset = 2;
    /**
     * Offset for number of lines config
     */
    const short kNumLinesOffset = 3;
    /**
     * Offset for style config
     */
    const short kStyleOffset = 5;
    /**
     * Default instruction command
     */
    const std::vector<unsigned char> kHardwareMonitor = {0xec, 0x52, 0x00, 0x00, 0x02, 0x00};
};
#endif // RYUJINIII_HARDWARE_MONITOR_STYLE_COMMAND_H
