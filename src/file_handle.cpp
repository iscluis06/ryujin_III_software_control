#include "file_handle.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include "ryujin_device.h"

FileHandle::FileHandle(const std::string &path) {
    this->ReadFile(path);
}

bool FileHandle::ReadFile(const std::string &path) {
    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        this->size = file.tellg();
        this->buffer = std::shared_ptr<unsigned char[]>(new unsigned char[this->size]);
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char *>(this->buffer.get()), this->size);
        file.close();
    } else {
        std::cerr << "Couldn't read file or invalid path" << std::endl;
        return false;
    }
    this->iterations = std::ceil(this->size / RyujinDevice::kDefaultBulkLength);
    return true;
};

std::vector<unsigned char> FileHandle::GetSizeToHex() {
    std::vector<unsigned char> array_size(3, 0);
    int i = 0;
    int value = this->size;
    while (true) {
        int hex_val = value % 16;
        if (i % 2 == 0) {
            array_size[i / 2] += hex_val;
        } else {
            array_size[i / 2] += hex_val * 16;
        }
        value = value / 16;
        i++;
        if (i > 5) {
            break;
        }
    }
    return array_size;
}
