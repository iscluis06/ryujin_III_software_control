#ifndef RYUJINIII_AMD_CORE_LINE_H
#define RYUJINIII_AMD_CORE_LINE_H

#include <filesystem>
#include "led_line/kernel_hardware_monitor.h"
/**
 * Class to show amd core temperatures by using kernel sensor driver
 */
class AmdCoreLine : public KernelHardwareMonitor {
public:
    /**
     * Default constructor
     */
    AmdCoreLine();
    /**
     * Default destructor
     */
    ~AmdCoreLine() override = default;
    /**
     * Returns the raw value from kernel driver into readable text
     * @param value Raw value from kernel driver
     * @return Processed text or empty on fail
     */
    std::string TransformValue(std::string value) override;
    /**
     * The title to show on led display, just above the value line
     * @return The title to show on led display
     */
    std::string GetTitle() override;

    /**
     * Utility method for testing purposes
     * @return The class name
     */
    std::string GetClassName() override;
};

#endif // RYUJINIII_AMD_CORE_LINE_H
