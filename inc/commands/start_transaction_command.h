#ifndef RYUJINIII_START_TRANSACTION_COMMAND_H
#define RYUJINIII_START_TRANSACTION_COMMAND_H

#include "base_command.h"

/**
 * Command that execute the start of a transaction
 */
class StartTransactionCommand : public BaseCommand {
public:
    /**
     * Constructor which sets the wrapper property
     * @param wrapper Reference to libusb wrapper
     */
    StartTransactionCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);

    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kStartTransaction = {0xec, 0xf1};
    /**
     * Default instruction to validate the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
};

#endif // RYUJINIII_START_TRANSACTION_COMMAND_H
