#include "build_args_parser.h"

#include "led_line/led_line_factory.h"

BuildArgsParser::BuildArgsParser() {
    this->parser = new args::ArgumentParser("Ryujin III Management Tool\n" + LedLineFactory::PrintCurrentImplements());
    this->help = new args::HelpFlag(*this->parser, "help", "Display help menu", {'h', "help"});
    this->turn_on = new args::Flag(*this->parser, "turn on", "Turn on the led display", {"lon"});
    this->turn_off = new args::Flag(*this->parser, "turn off", "Turn off the led display", {"loff"});
    this->default_gif = new args::Flag(*this->parser, "default gif", "Displays the default gif", {"default-gif"});
    this->hardware_monitor = new args::Flag(*this->parser, "hardware monitor",
                                            "Displays default hardware monitor, 1 line, mode cyberpunk, style 1 and "
                                            "ryujin liquid temp implement.\nCancel loop by using ctrl+c ",
                                            {"hw-monitor"});
    this->hardware_monitor_config =
            new args::Flag(*this->parser, "hardware monitor config",
                           "Configures a hardware monitor specify lines by using line parameters for "
                           "example --line1, --mode for mode "
                           "[galactic = 0, cyberpunk = 1], --style from 0 up to 3.\nExample: "
                           "--hw-monitor-config --line1=0 --mode=1 "
                           "--style=0 \nCancel loop by using ctrl+c",
                           {"hw-monitor-config"});
    this->line1 = new args::ValueFlag<int>(*this->parser, "line1",
                                           "Configures the first line for hardware monitor, refer to hardware "
                                           "monitor implementations for options ",
                                           {"line1"});
    this->line2 = new args::ValueFlag<int>(*this->parser, "line2",
                                           "Configures the first line for hardware monitor, refer to hardware "
                                           "monitor implementations for options ",
                                           {"line2"});
    this->line3 = new args::ValueFlag<int>(*this->parser, "line3",
                                           "Configures the first line for hardware monitor, refer to hardware "
                                           "monitor implementations for options ",
                                           {"line3"});
    this->git_repo_path = new args::ValueFlag<std::string>(
            *this->parser, "git repo path", "Specifies the path to the git repo for Git Last Commiter implementation",
            {"git-repo-path"});
    this->mode = new args::ValueFlag<int>(
            *this->parser, "mode",
            "Specifies the mode for hardware monitor, currently only galactic=0 and cyberpunk=1 available", {"mode"});
    this->style = new args::ValueFlag<int>(
            *this->parser, "style", "Specifies the style for hardware monitor, from 0 up to 3 available", {"style"});
    this->select_gif_from_memory =
            new args::ValueFlag<int>(*this->parser, "select gif", "Select a gif from memory", {"select-gif"});
    this->delete_from_memory = new args::ValueFlag<int>(*this->parser, "delete from memory", "Delete a gif from memory",
                                                        {"delete-from-memory"});
    this->upload_gif =
            new args::ValueFlag<std::string>(*this->parser, "upload gif",
                                             "Upload gif, it should be set along side select option, you must specify "
                                             "a memory slot to upload to",
                                             {"upload-gif"});
}
BuildArgsParser::~BuildArgsParser() {
    delete parser;
    delete help;
    delete turn_on;
    delete turn_off;
    delete default_gif;
    delete hardware_monitor;
    delete hardware_monitor_config;
    delete line1;
    delete line2;
    delete line3;
    delete git_repo_path;
    delete mode;
    delete style;
    delete select_gif_from_memory;
    delete delete_from_memory;
    delete upload_gif;
}
args::ArgumentParser *BuildArgsParser::GetParser() { return this->parser; }
