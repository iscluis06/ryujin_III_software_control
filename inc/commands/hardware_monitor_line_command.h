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
    HardwareMonitorLineCommand(const std::shared_ptr<LibUsbWrapperBase> &wrapper, std::shared_ptr<LedLineBase> base,
                               int line);
    bool Execute() override;

private:
    ByteUtils byte_utils_;
    std::vector<unsigned char> line_command = {0xec, 0x53, 0x00};
    // line command
    // unsigned char kHardwareMonitorLine[65] = {
    //         0xec, 0x53, 0x01, 0x4c, 0x69, 0x71, 0x75, 0x69, 0x64, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x2e, 0x0, 0x0,
    //         0x0,  0x0,  0x0,  0x0,  0x33, 0x31, 0x2e, 0x34, 0xe2, 0x84, 0x83, 0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
    //         0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
    //         0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0};
    std::shared_ptr<LedLineBase> base_;
    int line_;
};
#endif // RYUJINIII_HARDWARE_MONITOR_LINE_COMMAND_H
