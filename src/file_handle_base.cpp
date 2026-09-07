#include "file_handle_base.h"
const std::string FileHandleBase::GetPath() const { return this->path_; }
void FileHandleBase::SetBuffer(const std::shared_ptr<unsigned char[]> &buffer) { this->buffer_ = buffer; }
void FileHandleBase::SetSize(int size) { this->size_ = size; }
void FileHandleBase::SetIterations(int iterations) { this->iterations_ = iterations; }
void FileHandleBase::SetPath(const std::string &path) { this->path_ = path; }
std::vector<unsigned char> FileHandleBase::GetSizeToHex() {
    std::vector<unsigned char> array_size(3, 0);
    int i = 0;
    int value = this->size_;
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
bool FileHandleBase::Initialize() { return this->ReadFile(); }
const std::shared_ptr<unsigned char[]> FileHandleBase::GetBuffer() const { return this->buffer_; }
const int FileHandleBase::GetSize() const { return this->size_; }
const int FileHandleBase::GetIterations() const { return this->iterations_; }
