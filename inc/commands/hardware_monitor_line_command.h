#ifndef RYUJINIII_HARDWARE_MONITOR_LINE_COMMAND_H
#define RYUJINIII_HARDWARE_MONITOR_LINE_COMMAND_H
#include <memory>

#include "byte_utils.h"
#include "commands/base_command.h"
#include "led_line/led_line_base.h"

/**
 * Command to select the hardware monitor style
 * Based on: https://github.com/BrandonKynoch/asus-rog-ryujin-iii-linux-controller
 * Thanks to BrandonKynoch for his findings
 */
class HardwareMonitorLineCommand : public BaseCommand {
public:
    /**
     * Constructor for line command
     * @param wrapper Reference to libusb wrapper
     * @param base Led lide implementation to show on led display
     * @param line Line index to update on screen
     */
    HardwareMonitorLineCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, std::shared_ptr<LedLineBase> base, int line);
    /**
     * Default execution command
     * @return True on success, otherwise false
     */
    bool Execute() override;
    /**
     * Returns the class name for testing purposes
     * @return the name of the class
     */
    std::string GetClassName() const override;

private:
    /**
     * ByteUtils instance
     */
    ByteUtils byte_utils_;
    /**
     * Default line command instruction
     */
    std::vector<unsigned char> line_command = {0xec, 0x53, 0x00};
    /**
     * LedLineBase reference
     */
    std::shared_ptr<LedLineBase> base_;
    /**
     * Index of line to update
     */
    int line_;
};
#endif // RYUJINIII_HARDWARE_MONITOR_LINE_COMMAND_H
