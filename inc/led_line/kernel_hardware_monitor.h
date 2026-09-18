#ifndef RYUJINIII_KERNEL_HARDWARE_MONITOR_H
#define RYUJINIII_KERNEL_HARDWARE_MONITOR_H

#include <forward_list>
#include "led_line/led_line_base.h"
/**
 * Helper class to read sensor data for a given hardware name using kernel driver
 */
class KernelHardwareMonitor : public LedLineBase {
public:
    /**
     * Default constructor
     */
    KernelHardwareMonitor() = default;
    /**
     * Default destructor
     */
    virtual ~KernelHardwareMonitor() override = default;
    /**
     * Define a label to be shown led display, maximum 18 characters according to my findings
     * @return The value to shown on first line
     */
    virtual std::string GetLine() override;
    /**
     * Add a hardware label to hardware_labels_ list, which be used to match against all sensor of
     * a given hardware name, when a match is find the value counterpart will be used to obtain sensor data.
     * @param label Identifier for hardware label
     */
    void AddLabel(std::string label);
    /**
     * Setter for hardware_monitor_name_ property
     * @param name Hardware name to search for on kernel drivers
     */
    void SetHardwareMonitorName(const std::string &name);
    /**
     * Validates if hardware name set on hardware_monitor_name_ property exists on kernel drivers.
     * @return True if given hardware name found on kernel drivers
     */
    virtual bool IsHardwareNameAvailable();
    /**
     * Transforms the raw data to a more readable format
     * @param value raw data from kernel driver
     * @return The raw data process to a more readable format in success, otherwise empty
     */
    virtual std::string TransformValue(std::string value) = 0;
    /**
     * Define a label to be shown led display, maximum 18 characters according to my findings
     * @return The value to shown on first line
     */
    virtual std::string GetTitle() override = 0;

    /**
     * Utility method for testing purposes
     * @return The class name
     */
    virtual std::string GetClassName() override = 0;

private:
    /**
     * Search for the kernel driver matching hardware_monitor_name_ property and returns the path
     * @return The path to the kernel driver, on fail returns empty
     */
    virtual std::string GetHardwareMonitorNamePath();
    /**
     * Returns the sensor value from kernel driver
     * @return The raw data from sensor value
     */
    virtual std::string GetInputValue();
    /**
     * Default path to kernel drivers path
     */
    const std::string kHardwareMonitorPath = "/sys/class/hwmon";
    /**
     * Default suffix for kernel driver sensor data
     */
    const std::string kInputString = "input";
    /**
     * Property to hold the kernel driver hardware name
     */
    std::string hardware_monitor_name_;
    /**
     * List of labels to match agains to request sensor data
     */
    std::forward_list<std::string> hardware_labels_;
};

#endif // RYUJINIII_KERNEL_HARDWARE_MONITOR_H
