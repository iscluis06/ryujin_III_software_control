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
     * Default execution of command
     * @return True on success, otherwise false
     */
    bool Execute() override;

private:
    /**
     * Default command instruction
     */
    const unsigned char kStartTransaction[2] = {0xec, 0xf1};
    /**
     * Default instruction to validate the response
     */
    const unsigned char kValidateResponse[8] = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
};

#endif // RYUJINIII_START_TRANSACTION_COMMAND_H
