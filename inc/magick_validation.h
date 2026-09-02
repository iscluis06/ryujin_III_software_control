#ifndef RYUJINIII_MAGICK_VALIDATION_H
#define RYUJINIII_MAGICK_VALIDATION_H

/**
 * Class to validate if image magick command is installed
 */
class MagickValidation {
public:
  /**
   * Static method to validate presence of magick command
   * @return True if present otherwise false
   */
  static bool IsAvailable();
};

#endif // RYUJINIII_MAGICK_VALIDATION_H
