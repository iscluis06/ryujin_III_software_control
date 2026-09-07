#ifndef RYUJINIII_MAGICK_VALIDATION_H
#define RYUJINIII_MAGICK_VALIDATION_H
#include "transform_tool_base.h"

/**
 * Class to validate if image magick command is installed
 */
class MagickTool : public TransformToolBase {
public:
    /**
     * Method to validate presence of magick command
     * @return True if present otherwise false
     */
    bool IsAvailable() override;
    /**
     * Method to transform the file to a valid format for LED display
     * @param file_path Original file path
     * @param final_path Destination path
     * @return Return true if command succeed, otherwise false
     */
    bool Transform(std::string file_path, std::string final_path) override;
};

#endif // RYUJINIII_MAGICK_VALIDATION_H
