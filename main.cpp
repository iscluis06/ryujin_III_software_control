#include <cstring>
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <cmath>
#include <memory>
#include <args.hxx>

#include "inc/ryujin_device.h"


int main(int argc, char * argv[]) {
    args::ArgumentParser parser("Ryujin III Managment Tool");
    args::HelpFlag help(parser, "help", "Display help menu", {'h', "help"});
    args::Flag turn_on(parser, "turn on", "Turn on the led display", {"lon"});
    args::Flag turn_off(parser, "turn off", "Turn off the led display", {"loff"});
    args::Flag reset(parser, "reset", "Reset device and clear any pending instruction", {"reset"});
    args::ValueFlag<int> select_from_memory(parser, "select", "Select a gif from memory", {"gif"});
    args::ValueFlag<int> delete_from_memory(parser, "delete", "Delete a gif from memory", {"delete"});
    args::ValueFlag<std::string> upload_gif(parser, "upload_gif", "Upload gif", {"upload-gif"});
    if (argc < 2) {
        std::cout << "Missing option " << std::endl;
        std::cout << parser;
        exit(0);
    }
    try {
        parser.ParseCLI(argc, argv);
    }catch (args::Help) {
        std::cout << parser;
        exit(0);
    }catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        exit(1);
    }catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        exit(1);
    }
    RyujinDevice device{};


    if (!device.IsDeviceAvailable()) {
        std::cout << "Missing device ryujin III, closing now..." << std::endl;
        exit(0);
    }

    if (turn_on){ device.TurnOnLedDisplay(); }
    if (turn_off){ device.TurnOffLedDisplay(); }
    if (select_from_memory) { device.SelectGifFromMemory(args::get(select_from_memory)); }
    if (delete_from_memory) { device.DeleteFromMemory(args::get(select_from_memory)); }
    if (upload_gif) { device.UploadGif(args::get(upload_gif)); }
    if (reset) { device.Reset(); }

    return 0;
}
