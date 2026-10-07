#ifndef RYUJINIII_MAGICK_TOOL_JPEG_MOCK_H
#define RYUJINIII_MAGICK_TOOL_JPEG_MOCK_H

#include <gmock/gmock.h>
#include "magick_tool_jpeg.h"

class MagickToolJpegMock : public MagickToolJpeg {
public:
    MOCK_METHOD(bool, IsAvailable, (), (override));
    MOCK_METHOD(bool, Transform, (std::string file_path, std::string final_path), (override));
};

#endif // RYUJINIII_MAGICK_TOOL_JPEG_MOCK_H
