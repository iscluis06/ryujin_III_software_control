#ifndef RYUJINIII_FACTORY_H
#define RYUJINIII_FACTORY_H

#include <string>
#include "base_factory.h"
#include "libusb_wrapper.h"

/**
 * Default factory implementation
 */
class Factory : public BaseFactory {
public:
    /**
     * Default constructor
     * @param wrapper Reference to libusb wrapper instance
     */
    Factory(std::shared_ptr<LibUsbWrapperBase> wrapper);
    /**
     * Default destructor
     */
    ~Factory() override = default;
    /**
     * Method that returns a given class instance according to command string
     * @param command Name of the command to instance
     * @return Command instance on success otherwise false
     */
    std::unique_ptr<BaseCommand> GetCommand(std::string command) override;
    /**
     * Method that returns a given class instance according to command string
     * @param command Name of the command to instance
     * @param index Pass the value of index to command instance
     * @return Command instance on success otherwise false
     */
    std::unique_ptr<BaseCommand> GetCommand(std::string command, int index) override;
    /**
     * Method that returns a command chain according to command string
     * @param command Name of the command chain to instance
     * @param index Pass the value of index to command chain instance
     * @return Command chain instance on success otherwise false
     */
    std::unique_ptr<CommandChain> GetChain(std::string command, int index) override;
    /**
     * Method that returns a command chain according to command string
     * @param command Name of the command chain to instance
     * @param path Pass the value of path to command chain instance
     * @param index Pass the value of index to command chain instance
     * @return Command chain instance on success otherwise false
     */
    std::unique_ptr<CommandChain> GetChain(std::string command, std::string path, int index) override;

private:
    /**
     * Reference to libusb wrapper class
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
};

#endif // RYUJINIII_FACTORY_H
