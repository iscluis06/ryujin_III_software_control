#ifndef RYUJINIII_TRANSFORM_TOOL_MOCK_H
#define RYUJINIII_TRANSFORM_TOOL_MOCK_H

#include <gmock/gmock.h>
#include "transform_tool_base.h"

class TransformToolMock : public TransformToolBase {
public:
    MOCK_METHOD(bool, IsAvailable, (), (override));
    MOCK_METHOD(bool, Transform, (std::string file_path, std::string final_path), (override));
};

#endif // RYUJINIII_TRANSFORM_TOOL_MOCK_H
