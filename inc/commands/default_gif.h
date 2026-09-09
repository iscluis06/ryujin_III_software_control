#ifndef RYUJINIII_DEFAULT_GIF_H
#define RYUJINIII_DEFAULT_GIF_H
#include "base_command.h"

/**
 * Command for setting default gif into display
 */
class DefaultGifCommand : public BaseCommand {
public:
    /**
     * Constructor which also sets the reference to wrapper
     * @param wrapper Reference to libusb wrapper
     */
    DefaultGifCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);
    /**
     * Default destructor
     */
    ~DefaultGifCommand() override = default;
    /**
     * Method to execute the command
     * @return True on success, otherwise false
     */
    bool Execute() override;
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() override;
    /**
     * Default instruction command
     */
    unsigned char kDefaultGIFInstruction[3] = {0xec, 0x51, 0x14};
};

#endif // RYUJINIII_DEFAULT_GIF_H
