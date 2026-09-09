#include "magick_tool.h"
#include <filesystem>

bool MagickTool::IsAvailable() { return std::system("magick --version > /dev/null") == 0; }

bool MagickTool::Transform(std::string file_path, std::string final_path) {
    std::string magick_transform("magick " + file_path +
                                 " -coalesce -dispose 1 -resize 320x240! -background black -dither "
                                 "FloydSteinberg -remap netscape: -colors 64 " +
                                 final_path + " && truncate -s %4096 " + final_path);
    return std::system(magick_transform.c_str()) == 0;
}
