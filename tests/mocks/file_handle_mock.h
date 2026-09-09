#ifndef RYUJINIII_FILE_HANDLE_MOCK_H
#define RYUJINIII_FILE_HANDLE_MOCK_H

#include <gmock/gmock.h>
#include "file_handle_base.h"

class FileHandleMock : public FileHandleBase {
public:
    MOCK_METHOD(bool, Initialize, (), ());
    MOCK_METHOD(bool, ReadFile, (), (override));
    MOCK_METHOD(int, GetIterations, (), ());
};

#endif // RYUJINIII_FILE_HANDLE_MOCK_H
