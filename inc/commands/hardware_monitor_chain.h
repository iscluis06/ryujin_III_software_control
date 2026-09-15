#ifndef RYUJINIII_HARDWARE_MONITOR_CHAIN_H
#define RYUJINIII_HARDWARE_MONITOR_CHAIN_H
#include <list>
#include <memory>
#include "command_chain.h"
#include "led_line/led_line_factory.h"
#include "ryujin_constants.h"
#include "stores/hardware_status_store.h"

/**
 * Chain of commands to execute hardware monitor,
 * by default will execute a infinity loop until
 * ctrl+c is introduced.
 */
class HardwareMonitorChain : public CommandChain {
public:
    /**
     * Constructs the default hardware monitor chain.<br>
     * Currently valid modes are cyberpunk = 1 and galactic = 0.<br>
     * Also mode custom = 3, is available but currently unimplemented.<br>
     * Style will change the background design, both galactic and cyberpunk range from 0-3, 4 styles.<br>
     * line1 specifies which data led display should monitor.<br>
     * Reefer to led_line_factory for current monitor implementations.
     * @param wrapper Wrapper to libusb library
     * @param mode Defaults mode to cyberpunk
     * @param style Defaults background to style1
     * @param line1 Defaults to ryujin_liquid_temp monitor
     */
    HardwareMonitorChain(
            std::shared_ptr<LibUsbWrapperBase> wrapper,
            RyujinConstants::MonitorMode mode = RyujinConstants::MonitorMode::PUNK,
            RyujinConstants::MonitorStyle style = RyujinConstants::MonitorStyle::STYLE01,
            LedLineFactory::LedLineImplementations line1 = LedLineFactory::LedLineImplementations::RYUJIN_LIQUID_TEMP);
    /**
     * Currently valid modes are cyberpunk = 1 and galactic = 0.<br>
     * Also mode custom = 3, is available but currently unimplemented.<br>
     * Style will change the background design, both galactic and cyberpunk range from 0-3, 4 styles.<br>
     * line1 specifies which data led display should monitor, on line1.<br>
     * line2 specifies which data led display should monitor, on line2.<br>
     * @param wrapper Wrapper to libusb library
     * @param mode Select mode to display on led screen
     * @param style Select the background style to display
     * @param line1 Specifies which data led display should monitor, on line1
     * @param line2 Specifies which data led display should monitor, on line2.<br>
     * Reefer to led_line_factory for current monitor implementations.
     */
    HardwareMonitorChain(std::shared_ptr<LibUsbWrapperBase> wrapper, RyujinConstants::MonitorMode mode,
                         RyujinConstants::MonitorStyle style, LedLineFactory::LedLineImplementations line1,
                         LedLineFactory::LedLineImplementations line2);
    /**
     * Currently valid modes are cyberpunk = 1 and galactic = 0.<br>
     * Also mode custom = 3, is available but currently unimplemented.<br>
     * Style will change the background design, both galactic and cyberpunk range from 0-3, 4 styles.<br>
     * line1 specifies which data led display should monitor, on line1.<br>
     * line2 specifies which data led display should monitor, on line2.<br>
     * line3 specifies which data led display should monitor, on line3.<br>
     * @param wrapper Wrapper to libusb library
     * @param mode Select mode to display on led screen
     * @param style Select the background style to display
     * @param line1 Specifies which data led display should monitor, on line1
     * @param line2 Specifies which data led display should monitor, on line2
     * @param line3 Specifies which data led display should monitor, on line3.<br>
     * Reefer to led_line_factory for current monitor implementations.
     */
    HardwareMonitorChain(std::shared_ptr<LibUsbWrapperBase> wrapper, RyujinConstants::MonitorMode mode,
                         RyujinConstants::MonitorStyle style, LedLineFactory::LedLineImplementations line1,
                         LedLineFactory::LedLineImplementations line2, LedLineFactory::LedLineImplementations line3);
    /**
     * Execute the hardware monitor into a infinity loop
     * @return True on success, otherwise false
     */
    bool Execute() override;
    /**
     * Static global method to stop the infinity loop when ctrl+c is trigger
     * @param signal Catch signal
     */
    static void StopLoop(int signal);
    /**
     * Utility method to return led line factory to configure factory parameters
     * @return A reference to the led line factory class
     */
    std::shared_ptr<LedLineFactory> GetLedLineFactory();

private:
    /**
     * Property to define the number of lines to show on led display<br>
     * 0x0 = 1 line, 0x1 = 2 lines, 0x2 = 3 lines<br>
     * Thanks @BrandonKynoch for your findings
     */
    RyujinConstants::LinesConfig lines_config_ = RyujinConstants::LinesConfig::LINES1;
    /**
     * Flag that runs the infinity loop for hardware monitor
     */
    static bool running_;
    /**
     * Reference to libusb wrapper
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
    /**
     * Reference to Hardware Status Store
     */
    std::shared_ptr<HardwareStatusStore> store_;
    /**
     * Reference to led line factory
     */
    std::shared_ptr<LedLineFactory> led_line_factory_;
    /**
     * Property that defines the mode to display on led screen
     */
    RyujinConstants::MonitorMode mode_;
    /**
     * Property that defines the background style to show on led screen
     */
    RyujinConstants::MonitorStyle style_;
    /**
     * List of selected led line implementations to show on led screen
     */
    std::list<LedLineFactory::LedLineImplementations> lines_;
};
#endif // RYUJINIII_HARDWARE_MONITOR_CHAIN_H
