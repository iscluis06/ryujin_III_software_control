#ifndef RYUJINIII_SHOW_JPEG_COMMAND_H
#define RYUJINIII_SHOW_JPEG_COMMAND_H

#include "commands/base_command.h"

/**
 * Command to show a JPEG from selected memory slot
 */
class ShowJpegCommand : public BaseCommand {
public:
    /**
     * Default constructor
     * @param base Reference to libusb wrapper
     * @param index Memory slot to select
     */
    ShowJpegCommand(std::shared_ptr<LibUsbWrapperBase> base, int index);
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    std::vector<unsigned char> kShowJpegCommand = {0xec, 0x5d, 0x0, 0x1, 0x4, 0x0, 0x6, 0x5};
    /**
     * Index for the memory slot
     */
    const int kShowJpegIndex = 6;
};

#endif // RYUJINIII_SHOW_JPEG_COMMAND_H
