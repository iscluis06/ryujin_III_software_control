#include "tools/magick_tool_jpeg.h"
#include <filesystem>

bool MagickToolJpeg::IsAvailable() { return std::system("magick --version > /dev/null") == 0; }

bool MagickToolJpeg::Transform(std::string file_path, std::string final_path) {
    std::string magick_transform("magick " + file_path +
                                 " -resize 320x240! -background white -remap netscape: " + final_path);
    return std::system(magick_transform.c_str()) == 0;
}
