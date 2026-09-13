#ifndef RYUJINIII_KERNEL_HARDWARE_MONITOR_H
#define RYUJINIII_KERNEL_HARDWARE_MONITOR_H

#include <forward_list>


#include "led_line/led_line_base.h"

class KernelHardwareMonitor : public LedLineBase {
public:
    KernelHardwareMonitor() = default;
    virtual ~KernelHardwareMonitor() override = default;
    virtual std::string GetLine() override;
    void AddLabel(std::string label);
    void SetHardwareMonitorName(std::string name);
    virtual bool IsHardwareNameAvailable();
    virtual std::string TransformValue(std::string value) = 0;
    virtual std::string GetTitle() override = 0;

private:
    virtual std::string GetHardwareMonitorNamePath();
    virtual std::string GetInputValue();
    const std::string kHardwareMonitorPath = "/sys/class/hwmon";
    const std::string kInputString = "input";
    std::string hardware_monitor_name_;
    std::forward_list<std::string> hardware_labels_;
};

#endif // RYUJINIII_KERNEL_HARDWARE_MONITOR_H
