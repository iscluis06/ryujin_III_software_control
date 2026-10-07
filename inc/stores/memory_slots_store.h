#ifndef RYUJINIII_MEMORY_SLOTS_H
#define RYUJINIII_MEMORY_SLOTS_H

#include <array>
#include <string>

/**
 * Memory slots store, it will hold all slots data for jpegs and gifs.
 * <br>It will also save the data onto specify path from constructor.
 */
class MemorySlotsStore {
public:
    /**
     * Enum class to select between gif and jpeg
     */
    enum class SlotType { GIF = 0, JPEG = 1 };
    /**
     * Default constructor
     * @param path Path to a directory were to save data
     */
    MemorySlotsStore(std::string path);
    /**
     * Default destructor
     */
    virtual ~MemorySlotsStore() = default;
    /**
     * Updates the file slots, using the data from the array properties (_slots_)
     */
    virtual void UpdateSlots();
    /**
     * Method that updates a slot index of the selected slot type with the given path value.
     * @param index Index to update on slot property
     * @param path Path to set into slot variable
     * @param type Selected slot type
     */
    virtual void WriteSlot(int index, const std::string &path, SlotType type = SlotType::GIF);
    /**
     * Cleans the selected property slot index
     * @param index Index to update on slot property
     * @param type Selected slot type
     */
    virtual void RemoveSlot(int index, SlotType type = SlotType::GIF);
    /**
     * Prints all the slots onto standard output
     */
    virtual void PrintAll();

private:
    /**
     * Update the selected slot type into path + file (selected slot type)
     * @param type Selected slot type
     */
    void UpdateSlot(SlotType type);
    /**
     * Prints the selected slot type onto standard output and prints the title as header
     * @param type Selected slot type
     * @param title Header to print to standard output
     */
    void PrintSlots(SlotType type, const std::string &title);
    /**
     * Method that initializes a slot property with the data from the specified file_path
     * @param file_path Full file path to read in order to initialize slot property
     * @param array_reference Reference to slot property to update
     */
    void ReadSlots(std::string file_path, std::array<std::string, 10> &array_reference);
    /**
     * Array of gifs paths to keep track of memory slots
     */
    std::array<std::string, 10> gif_slots_;
    /**
     * Array of jpegs paths to keep track of memory slots
     */
    std::array<std::string, 10> jpeg_slots_;
    /**
     * Default gif file name
     */
    const std::string gif_file = "gif_array";
    /**
     * Default jpeg file name
     */
    const std::string jpeg_file = "jpeg_array";
    /**
     * Path to persistence directory
     */
    std::string path_;
};

#endif // RYUJINIII_MEMORY_SLOTS_H
