#include "file_handle.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include "ryujin_device.h"

bool FileHandle::ReadFile() {
    std::ifstream file(this->GetPath(), std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        this->SetSize(file.tellg());
        this->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[this->GetSize()]));
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char *>(this->GetBuffer().get()), this->GetSize());
        file.close();
    } else {
        std::cerr << "Couldn't read file or invalid path" << std::endl;
        return false;
    }
    this->SetIterations(std::ceil(this->GetSize() / RyujinDevice::kDefaultBulkLength));
    this->SetIterations(this->GetIterations() == 0 ? 1 : this->GetIterations());
    return true;
};
