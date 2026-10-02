#ifndef RYUJINIII_MEMORY_SLOTS_H
#define RYUJINIII_MEMORY_SLOTS_H

#include <array>
#include <string>

class MemorySlotsStore {
public:
    enum class SlotType { GIF = 0, JPEG = 1 };
    MemorySlotsStore(std::string path);
    bool UpdateSlots();
    bool WriteSlot(int index, const std::string &path, SlotType type = SlotType::GIF);
    bool RemoveSlot(int index, SlotType type = SlotType::GIF);
    void PrintAll();

private:
    void PrintSlots(SlotType type, const std::string &title);
    void ReadSlots(std::string file_path, std::array<std::string, 10> &array_reference);
    std::array<std::string, 10> gif_slots_;
    std::array<std::string, 10> jpeg_slots_;
    const std::string gif_file = "gif_array";
    const std::string jpeg_file = "jpeg_array";
    std::string path_;
};

#endif // RYUJINIII_MEMORY_SLOTS_H
