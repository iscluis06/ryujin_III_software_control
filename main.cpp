#include "magick_validation.h"

#include <args.hxx>
#include <cmath>
#include <iostream>

#include "inc/ryujin_device.h"

int main(int argc, char *argv[]) {
  args::ArgumentParser parser("Ryujin III Managment Tool");
  args::HelpFlag help(parser, "help", "Display help menu", {'h', "help"});
  args::Flag turn_on(parser, "turn on", "Turn on the led display", {"lon"});
  args::Flag turn_off(parser, "turn off", "Turn off the led display", {"loff"});
  args::ValueFlag<int> select_gif_from_memory(
      parser, "select-gif", "Select a gif from memory", {"select-gif"});
  args::ValueFlag<int> delete_from_memory(
      parser, "delete", "Delete a gif from memory", {"delete"});
  args::ValueFlag<std::string> upload_gif(
      parser, "upload-gif",
      "Upload gif, it should be set along side select option, you must specify "
      "a memory slot to upload to",
      {"upload-gif"});
  if (!MagickValidation::IsAvailable()) {
    std::cout << "Image Magick(command magick) is missing, please install it "
                 "or make it available "
                 "to PATH variable."
              << std::endl;
    std::cout
        << "Upload function will be disabled until image magick installed. "
        << std::endl;
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
  RyujinDevice device{};

  if (turn_on) {
    device.TurnOnLedDisplay();
  }
  if (turn_off) {
    device.TurnOffLedDisplay();
  }
  if (!upload_gif && select_gif_from_memory) {
    device.SelectGifFromMemory(args::get(select_gif_from_memory));
  }
  if (delete_from_memory) {
    device.DeleteFromMemory(args::get(select_gif_from_memory));
  }
  if (upload_gif && select_gif_from_memory) {
    device.UploadGif(args::get(upload_gif),
                     static_cast<short>(args::get(select_gif_from_memory)));
  } else if (upload_gif && !select_gif_from_memory) {
    std::cerr
        << "This option must be set along side the select_from_memory option"
        << std::endl;
  }
}
