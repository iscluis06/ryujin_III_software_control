#ifndef RYUJINIII_BASE_COMMAND_H
#define RYUJINIII_BASE_COMMAND_H

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "wrappers/libusb_wrapper_base.h"
/**
 * Abstract class for testing purposes
 */
class BaseCommand {
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
     * Default method to execute command
     * @return True on success, otherwise false
     */
    virtual bool Execute();

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
    virtual std::string GetClassName() const;

    void SetInstruction(std::vector<unsigned char> instruction);
    void SetTimeout(int timeout);
    void SetValidationMessage(std::vector<unsigned char> validation_message);
    void ShouldReadBack(bool read_back);
    std::vector<unsigned char> GetMessageBack();
    void SetCallBackFunction(std::function<void()> function_pointer);
    void SetEndpointOut(int endpoint_out);
    void SetEndpointIn(int endpoint_in);
    void SetResponseBackSize(int size);

private:
    /**
     * Wrapper reference
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;

    std::vector<unsigned char> instruction_;
    int timeout_ = 0;
    std::vector<unsigned char> validation_message_;
    bool read_back_ = false;
    std::vector<unsigned char> message_back_;
    std::function<void()> callback_;
    int endpoint_out_;
    int endpoint_in_;
    int response_back_size_ = 65;
};

#endif // RYUJINIII_BASE_COMMAND_H
