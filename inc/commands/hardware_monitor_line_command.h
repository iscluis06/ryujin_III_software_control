#ifndef RYUJINIII_HARDWARE_MONITOR_LINE_COMMAND_H
#define RYUJINIII_HARDWARE_MONITOR_LINE_COMMAND_H
/**
 * Command to select the hardware monitor style
 * Based on: https://github.com/BrandonKynoch/asus-rog-ryujin-iii-linux-controller
 * Thanks to BrandonKynoch for his findings
 */

#include <memory>

#include "byte_utils.h"
#include "commands/base_command.h"
#include "led_line/led_line_base.h"

class HardwareMonitorLineCommand : public BaseCommand {
public:
    HardwareMonitorLineCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, std::shared_ptr<LedLineBase> base, int line);
    bool Execute() override;
    std::string GetClassName() const override;

private:
    ByteUtils byte_utils_;
    std::vector<unsigned char> line_command = {0xec, 0x53, 0x00};
    std::shared_ptr<LedLineBase> base_;
    int line_;
};
#endif // RYUJINIII_HARDWARE_MONITOR_LINE_COMMAND_H
