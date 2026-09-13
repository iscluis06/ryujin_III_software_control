#include "magick_tool.h"

#include <args.hxx>
#include <cmath>
#include <iostream>

#include "commands/base_command.h"
#include "commands/command_chain.h"
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
    args::Flag default_gif(parser, "default gif", "Displays the default gif", {"default_gif"});
    args::Flag hardware_monitor(parser, "hardware monitor",
                                "Displays default hardware monitor, 1 line, mode cyberpunk, style 1 and ryujin liquid "
                                "temp implement.\nCancel loop by using ctrl+c",
                                {"hw_monitor"});
    args::Flag hardware_monitor_config(
            parser, "hardware monitor config",
            "Configures a hardware monitor specify lines by using line parameters for example --line1, --mode for mode "
            "[galactic = 0, cyberpunk = 1], --style from 0 up to 3.\nExample: --hw_monitor_config --line1=0 --mode=1 "
            "--style=0 \nCancel loop by using ctrl+c",
            {"hw_monitor_config"});
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
            parser, "git_repo_path", "Specifies the path to the git repo for Git Last Commiter implementation",
            {"git-repo"});
    args::ValueFlag<int> mode(
            parser, "mode",
            "Specifies the mode for hardware monitor, currently only galactic=0 and cyberpunk=1 available", {"mode"});
    args::ValueFlag<int> style(parser, "style", "Specifies the style for hardware monitor, from 0 up to 3 available",
                               {"style"});
    args::ValueFlag<int> select_gif_from_memory(parser, "select-gif", "Select a gif from memory", {"select-gif"});
    args::ValueFlag<int> delete_from_memory(parser, "delete", "Delete a gif from memory", {"delete"});
    args::ValueFlag<std::string> upload_gif(parser, "upload-gif",
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
    std::shared_ptr<BaseCommand> base_command = nullptr;
    std::shared_ptr<CommandChain> base_chain = nullptr;
    if (turn_on) {
        base_command = factory.GetCommand("turn_on");
    } else if (turn_off) {
        base_command = factory.GetCommand("turn_off");
    } else if (default_gif) {
        base_command = factory.GetCommand("default_gif");
    } else if (hardware_monitor) {
        base_chain = factory.GetChain("hw_monitor");
    } else if (hardware_monitor_config) {
        if (!line1 || !mode || !style) {
            std::cerr << "You must set at least line1, mode and style alongside hardware monitor config" << std::endl;
            return 1;
        }
        auto config = HardwareMonitorChainConfig(device.GetWrapper());
        config.AddLine(args::get(line1));
        config.SetMode(args::get(mode));
        config.SetStyle(args::get(style));
        if (line2) {
            config.AddLine(args::get(line2));
        }
        if (line3) {
            config.AddLine(args::get(line3));
        }
        if (git_repo_path) {
            config.SetGitPath(args::get(git_repo_path));
        }
        base_chain = config.GetChain();
    } else if (!upload_gif && select_gif_from_memory) {
        base_command = factory.GetCommand("select_gif_from_memory", args::get(select_gif_from_memory));
    } else if (delete_from_memory) {
        base_chain = factory.GetChain("delete_from_memory", args::get(delete_from_memory));
    } else if (upload_gif && select_gif_from_memory) {
        base_chain = factory.GetChain("upload_gif", args::get(upload_gif),
                                      static_cast<short>(args::get(select_gif_from_memory)));
    } else if (upload_gif && !select_gif_from_memory) {
        std::cerr << "This option must be set along side the select_from_memory option" << std::endl;
    }
    if (!base_command && !base_chain) {
        std::cerr << "Command not found" << std::endl;
        return 1;
    }
    int result =
            (base_command && base_command->Execute() == true) || (base_chain && base_chain->Execute() == true) ? 0 : 1;
    return result;
}
