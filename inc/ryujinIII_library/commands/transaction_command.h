#ifndef RYUJINIII_TRANSACTION_COMMAND_H
#define RYUJINIII_TRANSACTION_COMMAND_H

#include <memory>
#include "base_command.h"

/**
 * Command start a transaction
 */
class TransactionCommand : public BaseCommand {
public:
    /**
     * Constructor which sets the wrapper property
     * @param wrapper Reference to libusb wrapper
     */
    TransactionCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);

    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    std::string GetClassName() const override;

private:
    /**
     * Default command instruction
     */
    const std::vector<unsigned char> kTransaction = {0xec, 0x71, 0x01, 0x01};
    /**
     * Default instruction to validate the response
     */
    const std::vector<unsigned char> kValidateResponse = {0xec, 0x71};
};

#endif // RYUJINIII_TRANSACTION_COMMAND_H
