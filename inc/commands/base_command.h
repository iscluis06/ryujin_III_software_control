#ifndef RYUJINIII_BASE_COMMAND_H
#define RYUJINIII_BASE_COMMAND_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "execute_base.h"
#include "ryujin_constants.h"
#include "wrappers/libusb_wrapper_base.h"
/**
 * Abstract class for testing purposes
 */
class BaseCommand : public ExecuteBase {
public:
    /**
     * Constructor for base command class
     * @param wrapper Reference to libusb wrapper
     */
    BaseCommand(std::shared_ptr<LibUsbWrapperBase> wrapper);

    /**
     * Virtual destructor for abstraction
     */
    virtual ~BaseCommand() = default;

    /**
     * Default method to execute command.
     * It will execute only interrupt transfers:<br>It first execute an output transfer
     * sending the instruction set by instruction_ property through output endpoint
     * set by endpoint_out_ property. <br>If read_back_ property is set to true,
     * a transfer to input endpoint will be executed, all input transfers are
     * save into message_back_.<br>If callback_ property is set, the function
     * specified will be call it.<br>Finally if validation_message_ is set,
     * then the value from message_back_ will be validate it against validation_message_;
     * @return True on success, otherwise false
     */
    virtual bool Execute() override;

    /**
     *  Method to validate message argument
     * @param message Validates if given message is valid, it compares against
     * validation_message_ property
     * @return True if validation pass, otherwise false
     */
    [[nodiscard]] bool IsMessageValid(const std::vector<unsigned char> &message) const;

    /**
     * Return a shared_ptr to the wrapper reference
     * @return The wrapper reference
     */
    [[nodiscard]] std::shared_ptr<LibUsbWrapperBase> GetWrapper() const;
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    [[nodiscard]] virtual std::string GetClassName() const = 0;

    /**
     * Sets the instruction for the interrupt transfer, it will automatically pad it to 65 characters,
     * adding 0's.
     * @param instruction Instruction to set
     */
    void SetInstruction(const std::vector<unsigned char> &instruction);
    /**
     * Set's a timeout before reading the input endpoint
     * @param timeout Timeout to wait before reading from input endpoint
     */
    void SetTimeout(int timeout);
    /**
     * Sets the validation message to validate the response back from input endpoint.
     * ShouldReadBack most be set alongside this option.
     * @param validation_message Message to use to validate the response from input endpoint
     */
    void SetValidationMessage(std::vector<unsigned char> validation_message);
    /**
     * Sets the flag to read back from input endpoint not necessarily to validate the response back.
     * @param read_back If true execute will read back from input endpoint after sending a message
     * through output endpoint.
     */
    void ShouldReadBack(bool read_back);
    /**
     * Returns the response back after reading from input endpoint.
     * @return The message returned by input endpoint.
     */
    std::vector<unsigned char> GetMessageBack();
    /**
     * This will set a callback function to be executed after output and input endpoint transfers,
     * but before response validation.
     * @param function_pointer Pointer to callback function to execute
     */
    void SetCallBackFunction(std::function<void()> function_pointer);
    /**
     * Sets the output endpoint to execute the transfers against
     * @param endpoint_out The output endpoint to use to execute a transfer
     */
    void SetEndpointOut(int endpoint_out);
    /**
     * Sets the input endpoint to execute the transfers against
     * @param endpoint_input The input endpoint to use to execute a transfer
     */
    void SetEndpointIn(int endpoint_in);
    /**
     * Sets the default transfer size, so all messages can be pad using 0's during set instruction.
     * <br>This is mostly a helper function to change the default from ryujin constants.
     * @param size The default transfer size
     */
    void SetInterruptSize(int size);

private:
    /**
     * Wrapper reference
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
    /**
     * Reference to the instruction command to execute
     */
    std::vector<unsigned char> instruction_;
    /**
     * Timeout before executing a input endpoint transfer
     */
    int timeout_ = 0;
    /**
     * Message to validate against the response from input endpoint transfer.
     */
    std::vector<unsigned char> validation_message_;
    /**
     * Flag to specify if a transfer against input endpoint should be performed after output
     */
    bool read_back_ = false;
    /**
     * Reference to save the repsonse back from input endpoint, by default all responses
     * from input are saved.
     */
    std::vector<unsigned char> message_back_;
    /**
     * Reference to callback function.
     */
    std::function<void()> callback_;
    /**
     * Default output endpoint
     */
    int endpoint_out_ = -1;
    /**
     * Default output input
     */
    int endpoint_in_ = -1;
    /**
     * Default interrupt size for all transfers
     */
    int interrupt_size_ = RyujinConstants::kDefaultInterruptDataLength;
};

#endif // RYUJINIII_BASE_COMMAND_H
