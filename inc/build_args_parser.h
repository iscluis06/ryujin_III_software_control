#ifndef RYUJINIII_BUILDS_ARGS_PARSER_H
#define RYUJINIII_BUILDS_ARGS_PARSER_H

#include <args.hxx>
#include <forward_list>

class BuildArgsParser {
public:
    BuildArgsParser();
    BuildArgsParser(BuildArgsParser &parser_ref) = delete;
    bool operator=(BuildArgsParser &parser_ref) = delete;
    ~BuildArgsParser();
    args::ArgumentParser *GetParser();

private:
    std::forward_list<args::Base *> options;
    args::ArgumentParser *parser = nullptr;
};

#endif // RYUJINIII_BUILDS_ARGS_PARSER_H
