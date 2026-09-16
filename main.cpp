#include "magick_tool.h"

#include <args.hxx>
#include <cmath>
#include <iostream>

#include "build_args_parser.h"
#include "commands/base_command.h"
#include "factory.h"
#include "led_line/led_line_factory.h"
#include "ryujin_constants.h"
#include "ryujin_device.h"

int main(int argc, char *argv[]) {
    auto parser = new BuildArgsParser();
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
        parser->GetParser()->ParseCLI(argc, argv);
    } catch (args::Help &e) {
        std::cout << *parser->GetParser();
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
    auto execute_command = factory.GetCommand(*parser->GetParser());
    int result = execute_command != nullptr && execute_command->Execute() == true ? 0 : 1;
    return result;
}
