#ifndef RYUJINIII_BASE_COMMAND_H
#define RYUJINIII_BASE_COMMAND_H

#include <libusb_wrapper_base.h>
#include <memory>
#include <vector>
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
     * Constructor which also sets validation options
     * @param wrapper Reference to libusb wrapper
     * @param valid_message_back Default validation for response
     * @param valid_message_back_size Default size validation for response
     */
    BaseCommand(std::shared_ptr<LibUsbWrapperBase> wrapper, const unsigned char *valid_message_back,
                int valid_message_back_size);
    /**
     * Virtual destructor for abstraction
     */
    virtual ~BaseCommand() = default;

    /**
     * Default method to execute command
     * @return True on success, otherwise false
     */
    virtual bool Execute() = 0;

    /**
     *  Method to validate message argument
     * @param message Validates if given message is valid, it compares against
     * valid_message_back and valid_message_back_size properties
     * @return True if validation pass, otherwise false
     */
    [[nodiscard]] bool IsMessageValid(const std::vector<unsigned char> &message) const;

    /**
     * Return a shared_ptr to the wrapper reference
     * @return The wrapper reference
     */
    [[nodiscard]] std::shared_ptr<LibUsbWrapperBase> GetWrapper() const;

private:
    /**
     * Wrapper reference
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
    /**
     * Message to validate against a response
     */
    const unsigned char *valid_message_back_ = nullptr;
    /**
     * Size of response to validate against
     */
    int valid_message_back_size_ = 0;
};

#endif // RYUJINIII_BASE_COMMAND_H
