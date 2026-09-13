#ifndef RYUJINIII_AMD_CORE_LINE_H
#define RYUJINIII_AMD_CORE_LINE_H

#include <filesystem>
#include "led_line/kernel_hardware_monitor.h"

class AmdCoreLine : public KernelHardwareMonitor {
public:
    AmdCoreLine();
    ~AmdCoreLine() override = default;
    std::string TransformValue(std::string value) override;
    std::string GetTitle() override;
};

#endif // RYUJINIII_AMD_CORE_LINE_H
