#ifndef RYUJINIII_BASE_FACTORY_H
#define RYUJINIII_BASE_FACTORY_H

#include "commands/base_command.h"
#include "commands/command_chain.h"

class BaseFactory {
public:
    BaseFactory() = default;
    virtual ~BaseFactory() = default;
    virtual std::unique_ptr<BaseCommand> GetCommand(std::string command) = 0;
    virtual std::unique_ptr<BaseCommand> GetCommand(std::string command, int index) = 0;
    virtual std::unique_ptr<CommandChain> GetChain(std::string command, int index) = 0;
    virtual std::unique_ptr<CommandChain> GetChain(std::string command, std::string path, int index) = 0;
};

#endif // RYUJINIII_BASE_FACTORY_H
