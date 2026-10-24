#ifndef RYUJINIII_TRANSFORM_TOOL_BASE_H
#define RYUJINIII_TRANSFORM_TOOL_BASE_H
#include <string>
/**
 * Abstract class to specify a transforming tool for the gifs/jpegs files
 */
class TransformToolBase {
public:
    /**
     * Destructor
     */
    virtual ~TransformToolBase() = default;
    /**
     * Method to check if tool available on system
     * @return True if command available, otherwise false
     */
    virtual bool IsAvailable() = 0;
    /**
     * Method to transform the file to a valid format for LED display
     * @param file_path Original file path
     * @param final_path Destination path
     * @return Return true if command succeed, otherwise false
     */
    virtual bool Transform(std::string file_path, std::string final_path) = 0;
};

#endif // RYUJINIII_TRANSFORM_TOOL_BASE_H
