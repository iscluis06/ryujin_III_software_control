#ifndef RYUJINIII_BASE_COMMAND_CHAIN_H
#define RYUJINIII_BASE_COMMAND_CHAIN_H

/**
 * Helper abstract class to create a chain of commands (linked list)
 */
class BaseCommandChain {
public:
    /**
     * Default constructor
     */
    BaseCommandChain() = default;
    /**
     * Default destructor
     */
    virtual ~BaseCommandChain() = default;
    /**
     * Default method that executes the chain of commands
     * @return True on success, otherwise false
     */
    virtual bool Execute() = 0;
};

#endif // RYUJINIII_BASE_COMMAND_CHAIN_H
