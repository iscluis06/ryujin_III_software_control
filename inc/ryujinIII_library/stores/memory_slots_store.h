#ifndef RYUJINIII_MEMORY_SLOTS_H
#define RYUJINIII_MEMORY_SLOTS_H

#include <array>
#include <string>

#include "memory_slots_store_base.h"
#include "ryujin/ryujin_constants.h"

/**
 * Memory slots store, it will hold all slots data for jpegs and gifs.
 * <br>It will also save the data onto specify path from constructor.
 */
class MemorySlotsStore : public MemorySlotsStoreBase {
public:
    using slot_type = std::array<std::string, 10>;
    /**
     * Default constructor
     * @param path Path to a directory were to save data
     */
    MemorySlotsStore(std::string path);
    /**
     * Default destructor
     */
    ~MemorySlotsStore() override = default;
    /**
     * Updates the file slots, using the data from the array properties (_slots_)
     */
    void UpdateSlots() override;
    /**
     * Method that updates a slot index of the selected slot type with the given path value.
     * @param index Index to update on slot property
     * @param path Path to set into slot variable
     * @param type Selected slot type
     */
    void WriteSlot(int index, const std::string &path,
                   RyujinConstants::Slots type = RyujinConstants::Slots::GIF) override;
    /**
     * Cleans the selected property slot index
     * @param index Index to update on slot property
     * @param type Selected slot type
     */
    void RemoveSlot(int index, RyujinConstants::Slots type = RyujinConstants::Slots::GIF) override;
    /**
     * Prints all the slots onto standard output
     */
    void PrintAll() override;

    /**
     * Method to return a list of selected slot type
     * @param type Desired slot type to get
     * @return Return the list of the selected slot type
     */
    slot_type GetSlotsByType(RyujinConstants::Slots type = RyujinConstants::Slots::GIF) override;

private:
    /**
     * Update the selected slot type into path + file (selected slot type)
     * @param type Selected slot type
     */
    void UpdateSlot(RyujinConstants::Slots type) override;
    /**
     * Prints the selected slot type onto standard output and prints the title as header
     * @param type Selected slot type
     * @param title Header to print to standard output
     */
    void PrintSlots(RyujinConstants::Slots type, const std::string &title) override;
    /**
     * Method that initializes a slot property with the data from the specified file_path
     * @param file_path Full file path to read in order to initialize slot property
     * @param array_reference Reference to slot property to update
     */
    void ReadSlots(std::string file_path, slot_type &array_reference) override;
    /**
     * Array of gifs paths to keep track of memory slots
     */
    slot_type gif_slots_;
    /**
     * Array of jpegs paths to keep track of memory slots
     */
    slot_type jpeg_slots_;
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
