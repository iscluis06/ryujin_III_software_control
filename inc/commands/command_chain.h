#ifndef RYUJINIII_COMMAND_CHAIN_H
#define RYUJINIII_COMMAND_CHAIN_H

#include "base_command.h"
#include "base_command_chain.h"

/**
 * Default implementation for BaseCommandChain
 */
class CommandChain : public BaseCommandChain {
public:
  /**
   * Default constructor
   */
  CommandChain() = default;
  /**
   * Default destructor
   */
  ~CommandChain() override = default;
  /**
   * Default implementation of execution of chain commands
   * @return True on success, otherwise false
   */
  bool Execute() override;
  /**
   * Appends a command to the chain
   * @param command Command to append to chain
   */
  void AddCommand(BaseCommand *command);
  /**
   * Reference to current command to execute
   */
  BaseCommand *current_command = nullptr;
  /**
   * Reference to next CommandChain
   */
  CommandChain *next_command_chain = nullptr;
};

#endif // RYUJINIII_COMMAND_CHAIN_H
