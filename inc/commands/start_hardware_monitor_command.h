#ifndef RYUJINIII_HARDWARE_MONITOR_COMMAND_H
#define RYUJINIII_HARDWARE_MONITOR_COMMAND_H
#include "base_command.h"

/**
 * Command to activate hardware monitor
 * Based on: https://github.com/BrandonKynoch/asus-rog-ryujin-iii-linux-controller
 * Thanks to BrandonKynoch for his findings
 */
class StartHardwareMonitorCommand : public BaseCommand {
public:
    /**
     * Constructor for start hardware monitor command
     * @param wrapper Reference to libusb wrapper
     */
    StartHardwareMonitorCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);
    /**
     * Returns the class name for testing purposes
     * @return the name of the class
     */
    std::string GetClassName() const override;

private:
    /**
     * Default instruction command
     */
    const std::vector<unsigned char> kHardwareMonitor = {0xec, 0x51, 0x21};
};

#endif // RYUJINIII_HARDWARE_MONITOR_COMMAND_H
