#include "magick_tool.h"

#include <args.hxx>
#include <cmath>
#include <iostream>

#include "commands/base_command.h"
#include "commands/hardware_monitor_chain_config.h"
#include "factory.h"
#include "led_line/led_line_factory.h"
#include "ryujin_constants.h"
#include "ryujin_device.h"

int main(int argc, char *argv[]) {
    args::ArgumentParser parser("Ryujin III Management Tool\n" + LedLineFactory::PrintCurrentImplements());
    args::HelpFlag help(parser, "help", "Display help menu", {'h', "help"});
    args::Flag turn_on(parser, "turn on", "Turn on the led display", {"lon"});
    args::Flag turn_off(parser, "turn off", "Turn off the led display", {"loff"});
    args::Flag default_gif(parser, "default gif", "Displays the default gif", {"default-gif"});
    args::Flag hardware_monitor(parser, "hardware monitor",
                                "Displays default hardware monitor, 1 line, mode cyberpunk, style 1 and ryujin liquid "
                                "temp implement.\nCancel loop by using ctrl+c",
                                {"hw-monitor"});
    args::Flag hardware_monitor_config(
            parser, "hardware monitor config",
            "Configures a hardware monitor specify lines by using line parameters for example --line1, --mode for mode "
            "[galactic = 0, cyberpunk = 1], --style from 0 up to 3.\nExample: --hw-monitor-config --line1=0 --mode=1 "
            "--style=0 \nCancel loop by using ctrl+c",
            {"hw-monitor-config"});
    args::ValueFlag<int> line1(
            parser, "line1",
            "Configures the first line for hardware monitor, refer to hardware monitor implementations for options",
            {"line1"});
    args::ValueFlag<int> line2(
            parser, "line2",
            "Configures the first line for hardware monitor, refer to hardware monitor implementations for options",
            {"line2"});
    args::ValueFlag<int> line3(
            parser, "line3",
            "Configures the first line for hardware monitor, refer to hardware monitor implementations for options",
            {"line3"});
    args::ValueFlag<std::string> git_repo_path(
            parser, "git repo path", "Specifies the path to the git repo for Git Last Commiter implementation",
            {"git-repo-path"});
    args::ValueFlag<int> mode(
            parser, "mode",
            "Specifies the mode for hardware monitor, currently only galactic=0 and cyberpunk=1 available", {"mode"});
    args::ValueFlag<int> style(parser, "style", "Specifies the style for hardware monitor, from 0 up to 3 available",
                               {"style"});
    args::ValueFlag<int> select_gif_from_memory(parser, "select gif", "Select a gif from memory", {"select-gif"});
    args::ValueFlag<int> delete_from_memory(parser, "delete from memory", "Delete a gif from memory",
                                            {"delete-from-memory"});
    args::ValueFlag<std::string> upload_gif(parser, "upload gif",
                                            "Upload gif, it should be set along side select option, you must specify "
                                            "a memory slot to upload to",
                                            {"upload-gif"});
    // Right now only image magick command works and transform properly all gifs,
    // I may remove this functionality in favor of a C++ api/library
    std::shared_ptr<TransformToolBase> transform_tool = std::make_shared<MagickTool>();
    if (!transform_tool->IsAvailable()) {
        std::cout << "Image Magick(command magick) is missing, please install it "
                     "or make it available "
                     "to PATH variable."
                  << std::endl;
        std::cout << "Upload function will be disabled until image magick installed. " << std::endl;
    }
    if (argc < 2) {
        std::cout << "Missing option " << std::endl;
        std::cout << parser;
        exit(0);
    }
    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help &e) {
        std::cout << parser;
        exit(0);
    } catch (args::ParseError &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        exit(1);
    } catch (args::ValidationError &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        exit(1);
    }
    std::shared_ptr<LibUsbWrapper> wrapper = std::make_shared<LibUsbWrapper>();
    wrapper->SetTimeout(RyujinConstants::kDefaultTimeout);
    RyujinDevice device{wrapper};
    if (!device.Initialize()) {
        std::cout << "Device not found, exiting..." << std::endl;
        return 1;
    }
    Factory factory{device.GetWrapper()};
    auto execute_command = factory.GetCommand(parser);
    int result = execute_command != nullptr && execute_command->Execute() == true ? 0 : 1;
    return result;
}
