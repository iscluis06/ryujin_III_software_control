#ifndef RYUJINIII_BUILDS_ARGS_PARSER_H
#define RYUJINIII_BUILDS_ARGS_PARSER_H

#include <args.hxx>
#include <string>

class BuildArgsParser {
public:
    BuildArgsParser();
    BuildArgsParser(BuildArgsParser &parser_ref) = delete;
    bool operator=(BuildArgsParser &parser_ref) = delete;
    ~BuildArgsParser();
    args::ArgumentParser *GetParser();

private:
    args::ArgumentParser *parser = nullptr;
    args::HelpFlag *help = nullptr;
    args::Flag *turn_on = nullptr;
    args::Flag *turn_off = nullptr;
    args::Flag *default_gif = nullptr;
    args::Flag *hardware_monitor = nullptr;
    args::Flag *hardware_monitor_config = nullptr;
    args::ValueFlag<int> *line1 = nullptr;
    args::ValueFlag<int> *line2 = nullptr;
    args::ValueFlag<int> *line3 = nullptr;
    args::ValueFlag<std::string> *git_repo_path = nullptr;
    args::ValueFlag<int> *mode = nullptr;
    args::ValueFlag<int> *style = nullptr;
    args::ValueFlag<int> *select_gif_from_memory = nullptr;
    args::ValueFlag<int> *delete_from_memory = nullptr;
    args::ValueFlag<std::string> *upload_gif = nullptr;
};

#endif // RYUJINIII_BUILDS_ARGS_PARSER_H
