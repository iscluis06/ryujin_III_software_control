#include "build_args_parser.h"

#include "led_line/led_line_factory.h"

BuildArgsParser::BuildArgsParser() {
    this->parser = new args::ArgumentParser("Ryujin III Management Tool\n" + LedLineFactory::PrintCurrentImplements());
    this->options.emplace_front(new args::HelpFlag(*this->parser, "help", "Display help menu", {'h', "help"}));

    this->options.emplace_front(new args::Group(*this->parser, "", args::Group::Validators::Xor));
    args::Group *all_exclusive = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(
            new args::Group(*all_exclusive, "Display power (exclusive options)", args::Group::Validators::Xor));
    args::Group *display_power_group = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(
            new args::Group(*all_exclusive, "Speed config (exclusive options)", args::Group::Validators::Xor));
    args::Group *speed_config_group = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(new args::Group(*all_exclusive, "Information group", args::Group::Validators::Xor));
    args::Group *information_group = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(
            new args::Group(*all_exclusive, "Led display config (exclusive options)", args::Group::Validators::Xor));
    args::Group *led_display_config = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(
            new args::Group(*all_exclusive, "Hardware monitor default", args::Group::Validators::Xor));
    args::Group *hardware_monitor = dynamic_cast<args::Group *>(this->options.front());
    this->options.emplace_front(new args::Group(*all_exclusive,
                                                "Hardware monitor customization (All options must be specified)",
                                                args::Group::Validators::All));
    args::Group *hardware_monitor_customization = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(new args::Group(*all_exclusive, "Upload gif (All options must be specified)",
                                                args::Group::Validators::All));
    args::Group *upload_gif = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(new args::Group(*all_exclusive, "Upload jpeg (All options must be specified)",
                                                args::Group::Validators::All));
    args::Group *upload_jpeg = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(new args::Flag(*display_power_group, "turn on", "Turn on the led display", {"lon"}));
    this->options.emplace_front(new args::Flag(*display_power_group, "turn off", "Turn off the led display", {"loff"}));

    this->options.emplace_front(new args::ValueFlag<int>(*speed_config_group, "fan speed config", "Fan Speed config",
                                                         {"fan-speed-config"}));
    this->options.emplace_front(new args::ValueFlag<int>(*speed_config_group, "pump speed config", "Pump Speed config",
                                                         {"pump-speed-config"}));

    this->options.emplace_front(
            new args::Flag(*information_group, "show slots", "Displays available memory slots", {"show-slots"}));

    this->options.emplace_front(
            new args::Flag(*led_display_config, "default gif", "Displays the default gif", {"default-gif"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*led_display_config, "select gif", "Select a gif from memory", {"select-gif"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*led_display_config, "select jpeg", "Select a jpeg from memory", {"select-jpeg"}));
    this->options.emplace_front(new args::ValueFlagList<int>(*led_display_config, "slideshow",
                                                             "Creates a slideshow between gif images", {"slideshow"}));
    this->options.emplace_front(new args::ValueFlagList<int>(
            *led_display_config, "slideshow jpeg", "Creates a slideshow between jpeg images", {"slideshow-jpeg"}));
    this->options.emplace_front(
            new args::Flag(*led_display_config, "clock mode", "Activates clock mode", {"clock-mode"}));
    this->options.emplace_front(new args::ValueFlag<int>(*led_display_config, "delete a gif from memory",
                                                         "Delete a gif from memory", {"delete-gif"}));
    this->options.emplace_front(new args::ValueFlag<int>(*led_display_config, "delete a jpeg from memory",
                                                         "Delete a jpeg from memory", {"delete-jpeg"}));

    this->options.emplace_front(new args::Flag(*hardware_monitor, "hardware monitor",
                                               "Displays default hardware monitor, 1 line, mode cyberpunk, style 1 and "
                                               "ryujin liquid temp implement.\nCancel loop by using ctrl+c ",
                                               {"hw-monitor"}));
    this->options.emplace_front(
            new args::Flag(*hardware_monitor_customization, "hardware monitor config",
                           "Configures a hardware monitor specify lines by using line parameters for "
                           "example --line1, --mode for mode "
                           "[galactic = 0, cyberpunk = 1], --style from 0 up to 3.\nExample: "
                           "--hw-monitor-config --line1=0 --mode=1 "
                           "--style=0 \nCancel loop by using ctrl+c",
                           {"hw-monitor-config"}));
    this->options.emplace_front(new args::ValueFlag<int>(
            *hardware_monitor_customization, "mode",
            "Specifies the mode for hardware monitor, currently only galactic=0 and cyberpunk=1 available", {"mode"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*hardware_monitor_customization, "style",
                                     "Specifies the style for hardware monitor, from 0 up to 3 available", {"style"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*hardware_monitor_customization, "line1",
                                     "Configures the first line for hardware monitor, refer to hardware "
                                     "monitor implementations for options ",
                                     {"line1"}));

    this->options.emplace_front(new args::Group(*hardware_monitor_customization, "More hardware config options",
                                                args::Group::Validators::DontCare));
    args::Group *hardware_monitor_additional = dynamic_cast<args::Group *>(this->options.front());

    this->options.emplace_front(
            new args::ValueFlag<int>(*hardware_monitor_additional, "line2",
                                     "Configures the first line for hardware monitor, refer to hardware "
                                     "monitor implementations for options ",
                                     {"line2"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*hardware_monitor_additional, "line3",
                                     "Configures the first line for hardware monitor, refer to hardware "
                                     "monitor implementations for options ",
                                     {"line3"}));
    this->options.emplace_front(new args::ValueFlag<std::string>(
            *hardware_monitor_additional, "git repo path",
            "Specifies the path to the git repo for Git Last Commiter implementation", {"git-repo-path"}));


    this->options.emplace_front(
            new args::ValueFlag<std::string>(*upload_gif, "upload gif",
                                             "Upload gif, it should be set along side select option, you must specify "
                                             "a memory slot to upload to",
                                             {"upload-gif"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*upload_gif, "select gif", "Select a gif from memory", {"select-gif"}));
    this->options.emplace_front(
            new args::ValueFlag<std::string>(*upload_jpeg, "upload jpeg",
                                             "Upload jpeg, it should be set along side select option, you must specify "
                                             "a memory slot to upload to",
                                             {"upload-jpeg"}));
    this->options.emplace_front(
            new args::ValueFlag<int>(*upload_jpeg, "select jpeg", "Select a jpeg from memory", {"select-jpeg"}));
}

BuildArgsParser::~BuildArgsParser() {
    for (auto option: this->options) {
        delete option;
    }
    this->options.clear();
    delete parser;
}

args::ArgumentParser *BuildArgsParser::GetParser() { return this->parser; }
