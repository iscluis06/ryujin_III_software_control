#include "magick_tool.h"

#include <args.hxx>
#include <cmath>
#include <iostream>

#include "commands/base_command.h"
#include "commands/command_chain.h"
#include "factory.h"
#include "inc/ryujin_device.h"

int main(int argc, char *argv[]) {
    args::ArgumentParser parser("Ryujin III Managment Tool");
    args::HelpFlag help(parser, "help", "Display help menu", {'h', "help"});
    args::Flag turn_on(parser, "turn on", "Turn on the led display", {"lon"});
    args::Flag turn_off(parser, "turn off", "Turn off the led display", {"loff"});
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
    wrapper->SetTimeout(RyujinDevice::kDefaultTimeout);
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
    }
    if (turn_off) {
        base_command = factory.GetCommand("turn_off");
    }
    if (!upload_gif && select_gif_from_memory) {
        base_command = factory.GetCommand("select_gif_from_memory", args::get(select_gif_from_memory));
    }
    if (delete_from_memory) {
        base_chain = factory.GetChain("delete_from_memory", args::get(delete_from_memory));
    }
    if (upload_gif && select_gif_from_memory) {
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
