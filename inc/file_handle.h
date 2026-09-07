#ifndef RYUJINIII_FILE_HANDLE_H
#define RYUJINIII_FILE_HANDLE_H

#include "file_handle_base.h"

/**
 * Helper class to manage file operations.
 */
class FileHandle : public FileHandleBase {
public:
    /**
     * Default constructor
     */
    FileHandle() = default;

    ~FileHandle() override = default;

protected:
    /**
     * Method that reads all file data and initialize size, iterations and buffer.
     * @return True on success, false otherwise
     */
    bool ReadFile() override;
};

#endif // RYUJINIII_FILE_HANDLE_H
