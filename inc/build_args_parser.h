#ifndef RYUJINIII_BUILDS_ARGS_PARSER_H
#define RYUJINIII_BUILDS_ARGS_PARSER_H

#include <args.hxx>
#include <forward_list>

/**
 * Helper class to build the arguments parser
 */
class BuildArgsParser {
public:
    /**
     * Default constructor
     */
    BuildArgsParser();
    /**
     * Deleted copy constructor
     * @param parser_ref Reference to args parse instance
     */
    BuildArgsParser(BuildArgsParser &parser_ref) = delete;
    /**
     * Deleted asignment operator
     * @param parser_ref Reference to args parse instance
     * @return True if instances equal, otherwise false
     */
    bool operator=(BuildArgsParser &parser_ref) = delete;
    /**
     * Destructor
     */
    ~BuildArgsParser();
    /**
     * Process argument parser commands
     * @return Returns an instance of ArgumentParser
     */
    args::ArgumentParser *GetParser();

private:
    /**
     * Linked list of argument parser options
     */
    std::forward_list<args::Base *> options;
    /**
     * Defualt instance of argument parser
     */
    args::ArgumentParser *parser = nullptr;
};

#endif // RYUJINIII_BUILDS_ARGS_PARSER_H
