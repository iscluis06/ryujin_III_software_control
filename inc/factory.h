#ifndef RYUJINIII_FACTORY_H
#define RYUJINIII_FACTORY_H

#include <args.hxx>
#include <string>
#include "base_factory.h"
#include "wrappers/libusb_wrapper.h"

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
     * Method that returns a given class instance according to matching arguments
     * @param parser Reference to arguments parser
     * @return Command instance on success otherwise false
     */
    std::unique_ptr<ExecuteBase> GetCommand(args::ArgumentParser &parser) override;

private:
    /**
     * Reference to libusb wrapper class
     */
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
};

#endif // RYUJINIII_FACTORY_H
