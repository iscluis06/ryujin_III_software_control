#include "magick_validation.h"
#include <filesystem>

bool MagickValidation::IsAvailable() {
  return std::system("magick --version > /dev/null") == 0;
}
