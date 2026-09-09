#ifndef RYUJINIII_BASE_FACTORY_H
#define RYUJINIII_BASE_FACTORY_H

#include "commands/base_command.h"
#include "commands/command_chain.h"

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
     * Method that returns a given class instance according to command string
     * @param command Name of the command to instance
     * @return Command instance on success otherwise false
     */
    virtual std::unique_ptr<BaseCommand> GetCommand(std::string command) = 0;
    /**
     * Method that returns a given class instance according to command string
     * @param command Name of the command to instance
     * @param index Pass the value of index to command instance
     * @return Command instance on success otherwise false
     */
    virtual std::unique_ptr<BaseCommand> GetCommand(std::string command, int index) = 0;
    /**
     * Method that returns a command chain according to command string
     * @param command Name of the command chain to instance
     * @param index Pass the value of index to command chain instance
     * @return Command chain instance on success otherwise false
     */
    virtual std::unique_ptr<CommandChain> GetChain(std::string command, int index) = 0;
    /**
     * Method that returns a command chain according to command string
     * @param command Name of the command chain to instance
     * @param path Pass the value of path to command chain instance
     * @param index Pass the value of index to command chain instance
     * @return Command chain instance on success otherwise false
     */
    virtual std::unique_ptr<CommandChain> GetChain(std::string command, std::string path, int index) = 0;
};

#endif // RYUJINIII_BASE_FACTORY_H
