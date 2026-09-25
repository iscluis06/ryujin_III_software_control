#include "build_args_parser.h"

#include "led_line/led_line_factory.h"

BuildArgsParser::BuildArgsParser() {
    this->parser = new args::ArgumentParser("Ryujin III Management Tool\n" + LedLineFactory::PrintCurrentImplements());
    this->options.emplace_front(new args::HelpFlag(*this->parser, "help", "Display help menu", {'h', "help"}));
    this->options.emplace_front(new args::Flag(*this->parser, "turn on", "Turn on the led display", {"lon"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*this->parser, "fan speed config", "Fan Speed config", {"fan-speed-config"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*this->parser, "pump speed config", "Pump Speed config", {"pump-speed-config"}));
    this->options.emplace_front(new args::Flag(*this->parser, "turn off", "Turn off the led display", {"loff"}));
    this->options.emplace_front(
            new args::Flag(*this->parser, "default gif", "Displays the default gif", {"default-gif"}));
    this->options.emplace_front(new args::Flag(*this->parser, "hardware monitor",
                                               "Displays default hardware monitor, 1 line, mode cyberpunk, style 1 and "
                                               "ryujin liquid temp implement.\nCancel loop by using ctrl+c ",
                                               {"hw-monitor"}));
    this->options.emplace_front(
            new args::Flag(*this->parser, "hardware monitor config",
                           "Configures a hardware monitor specify lines by using line parameters for "
                           "example --line1, --mode for mode "
                           "[galactic = 0, cyberpunk = 1], --style from 0 up to 3.\nExample: "
                           "--hw-monitor-config --line1=0 --mode=1 "
                           "--style=0 \nCancel loop by using ctrl+c",
                           {"hw-monitor-config"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*this->parser, "line1",
                                     "Configures the first line for hardware monitor, refer to hardware "
                                     "monitor implementations for options ",
                                     {"line1"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*this->parser, "line2",
                                     "Configures the first line for hardware monitor, refer to hardware "
                                     "monitor implementations for options ",
                                     {"line2"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*this->parser, "line3",
                                     "Configures the first line for hardware monitor, refer to hardware "
                                     "monitor implementations for options ",
                                     {"line3"}));
    this->options.emplace_front(new args::ValueFlag<std::string>(
            *this->parser, "git repo path", "Specifies the path to the git repo for Git Last Commiter implementation",
            {"git-repo-path"}));
    this->options.emplace_front(new args::ValueFlag<int>(
            *this->parser, "mode",
            "Specifies the mode for hardware monitor, currently only galactic=0 and cyberpunk=1 available", {"mode"}));
    this->options.emplace_front(new args::ValueFlag<int>(
            *this->parser, "style", "Specifies the style for hardware monitor, from 0 up to 3 available", {"style"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*this->parser, "select gif", "Select a gif from memory", {"select-gif"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*this->parser, "select jpeg", "Select a jpeg from memory", {"select-jpeg"}));
    this->options.emplace_front(new args::ValueFlag<int>(*this->parser, "delete from memory",
                                                         "Delete a gif from memory", {"delete-from-memory"}));
    this->options.emplace_front(
            new args::ValueFlag<std::string>(*this->parser, "upload gif",
                                             "Upload gif, it should be set along side select option, you must specify "
                                             "a memory slot to upload to",
                                             {"upload-gif"}));
    this->options.emplace_front(
            new args::ValueFlag<std::string>(*this->parser, "upload jpeg",
                                             "Upload jpeg, it should be set along side select option, you must specify "
                                             "a memory slot to upload to",
                                             {"upload-jpeg"}));
}
BuildArgsParser::~BuildArgsParser() {
    for (auto option: this->options) {
        delete option;
    }
    this->options.clear();
    delete parser;
}
args::ArgumentParser *BuildArgsParser::GetParser() { return this->parser; }
