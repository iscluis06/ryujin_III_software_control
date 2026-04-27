#ifndef RYUJINIII_FILE_HANDLE_H
#define RYUJINIII_FILE_HANDLE_H

#include <memory>
#include <string>
#include <vector>

class FileHandle {
public:
    FileHandle(const std::string &path);

    std::vector<unsigned char> GetSizeToHex();

    std::shared_ptr<unsigned char[]> buffer;
    int size;
    int iterations;

private:
    bool ReadFile(const std::string &path);
};

#endif //RYUJINIII_FILE_HANDLE_H
