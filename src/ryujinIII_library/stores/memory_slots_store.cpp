#include "stores/memory_slots_store.h"

#include <filesystem>
#include <fstream>
#include <iostream>
MemorySlotsStore::MemorySlotsStore(std::string path) {
    this->path_ = std::move(path);
    this->ReadSlots(this->path_ + "/" + this->gif_file, this->gif_slots_);
    this->ReadSlots(this->path_ + "/" + this->jpeg_file, this->jpeg_slots_);
}

void MemorySlotsStore::ReadSlots(std::string file_path, std::array<std::string, 10> &array_reference) {
    if (!std::filesystem::exists(file_path)) {
        std::cerr << "File: " << file_path << " doesn't exists" << std::endl;
        return;
    }
    std::ifstream file_stream{file_path};
    std::string line;
    int i = 0;
    while (getline(file_stream, line)) {
        array_reference[i++] = line;
        if (i == 10) break;
    }
}
void MemorySlotsStore::WriteSlot(int index, const std::string &path, RyujinConstants::Slots type) {
    std::array<std::string, 10> &slot = type == RyujinConstants::Slots::GIF ? this->gif_slots_ : this->jpeg_slots_;
    if (std::filesystem::exists(slot[index])) {
        std::filesystem::remove(slot[index]);
    }
    slot[index] = path;
}
void MemorySlotsStore::RemoveSlot(int index, RyujinConstants::Slots type) {
    std::array<std::string, 10> &slot = type == RyujinConstants::Slots::GIF ? this->gif_slots_ : this->jpeg_slots_;
    if (std::filesystem::exists(slot[index])) {
        std::filesystem::remove(slot[index]);
    }
    slot[index] = "";
}

void MemorySlotsStore::UpdateSlots() {
    this->UpdateSlot(RyujinConstants::Slots::GIF);
    this->UpdateSlot(RyujinConstants::Slots::JPEG);
}

void MemorySlotsStore::PrintSlots(RyujinConstants::Slots type, const std::string &title) {
    std::array<std::string, 10> &slots = type == RyujinConstants::Slots::GIF ? this->gif_slots_ : this->jpeg_slots_;
    int i = 0;
    std::cout << title << std::endl;
    for (const std::string &slot: slots) {
        std::cout << "index[" << i++ << "]=" << slot << std::endl;
    }
    std::cout << std::endl;
}

void MemorySlotsStore::PrintAll() {
    this->PrintSlots(RyujinConstants::Slots::GIF, "GIFS");
    this->PrintSlots(RyujinConstants::Slots::JPEG, "JPEGS");
}

std::array<std::string, 10> MemorySlotsStore::GetSlotsByType(RyujinConstants::Slots type) {
    std::array<std::string, 10> &slots = type == RyujinConstants::Slots::GIF ? this->gif_slots_ : this->jpeg_slots_;
    return slots;
}

void MemorySlotsStore::UpdateSlot(RyujinConstants::Slots type) {
    std::string file_path_string = type == RyujinConstants::Slots::GIF ? this->gif_file : this->jpeg_file;
    std::array<std::string, 10> &slot = type == RyujinConstants::Slots::GIF ? this->gif_slots_ : this->jpeg_slots_;
    std::ofstream file_path{this->path_ + "/" + file_path_string, std::ios::trunc};
    std::string text = "";
    for (const std::string &line: slot) {
        text += line + "\n";
    }
    file_path.write(text.data(), static_cast<long>(text.size()));
    file_path.close();
}
