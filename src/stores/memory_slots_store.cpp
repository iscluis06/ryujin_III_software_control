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
bool MemorySlotsStore::WriteSlot(int index, const std::string &path, SlotType type) {
    std::array<std::string, 10> &slot = type == SlotType::GIF ? this->gif_slots_ : this->jpeg_slots_;
    if (std::filesystem::exists(slot[index])) {
        std::filesystem::remove(slot[index]);
    }
    slot[index] = path;
    return true;
}
bool MemorySlotsStore::RemoveSlot(int index, SlotType type) {
    std::array<std::string, 10> &slot = type == SlotType::GIF ? this->gif_slots_ : this->jpeg_slots_;
    if (std::filesystem::exists(slot[index])) {
        std::filesystem::remove(slot[index]);
    }
    slot[index] = "";
    return true;
}

bool MemorySlotsStore::UpdateSlots() {
    std::ofstream gif_slots{this->path_ + "/" + this->gif_file, std::ios::trunc};
    std::ofstream jpeg_slots{this->path_ + "/" + this->jpeg_file, std::ios::trunc};
    std::string text = "";
    for (const std::string &line: this->gif_slots_) {
        text += line + "\n";
    }
    gif_slots.write(text.data(), text.size());
    text = "";
    for (const std::string &line: this->jpeg_slots_) {
        text += line + "\n";
    }
    jpeg_slots.write(text.data(), text.size());
    gif_slots.close();
    jpeg_slots.close();
    return true;
}
void MemorySlotsStore::PrintSlots(SlotType type, const std::string &title) {
    std::array<std::string, 10> &slots = type == SlotType::GIF ? this->gif_slots_ : this->jpeg_slots_;
    int i = 0;
    std::cout << title << std::endl;
    for (const std::string &slot: slots) {
        std::cout << "index[" << i++ << "]=" << slot << std::endl;
    }
    std::cout << std::endl;
}

void MemorySlotsStore::PrintAll() {
    this->PrintSlots(SlotType::GIF, "GIFS");
    this->PrintSlots(SlotType::JPEG, "JPEGS");
}
