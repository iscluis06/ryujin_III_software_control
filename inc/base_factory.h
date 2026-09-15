#ifndef RYUJINIII_BASE_FACTORY_H
#define RYUJINIII_BASE_FACTORY_H

#include "commands/base_command.h"

/**
 * Abstract factory for testing purposes
 */
class BaseFactory {
public:
    /**
     * Default constructor
     */
    BaseFactory() = default;
    /**
     * Default destructor
     */
    virtual ~BaseFactory() = default;
    /**
     * Method that returns a given class instance according to matching arguments
     * @param parser Reference to arguments parser
     * @return Command instance on success otherwise false
     */
    virtual std::unique_ptr<ExecuteBase> GetCommand(args::ArgumentParser &parser) = 0;
};

#endif // RYUJINIII_BASE_FACTORY_H
