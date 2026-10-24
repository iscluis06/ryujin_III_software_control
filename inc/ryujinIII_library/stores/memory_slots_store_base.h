#ifndef RYUJINIII_MEMORY_SLOTS_STORE_BASE_H
#define RYUJINIII_MEMORY_SLOTS_STORE_BASE_H

#include <array>
#include <string>

#include "ryujin/ryujin_constants.h"

/**
 * Memory slots store, it will hold all slots data for jpegs and gifs.
 * <br>It will also save the data onto specify path from constructor.
 */
class MemorySlotsStoreBase {
public:
    using slot_type = std::array<std::string, 10>;
    /**
     * Default destructor
     */
    virtual ~MemorySlotsStoreBase() = default;
    /**
     * Updates the file slots, using the data from the array properties (_slots_)
     */
    virtual void UpdateSlots() = 0;
    /**
     * Method that updates a slot index of the selected slot type with the given path value.
     * @param index Index to update on slot property
     * @param path Path to set into slot variable
     * @param type Selected slot type
     */
    virtual void WriteSlot(int index, const std::string &path,
                           RyujinConstants::Slots type = RyujinConstants::Slots::GIF) = 0;
    /**
     * Cleans the selected property slot index
     * @param index Index to update on slot property
     * @param type Selected slot type
     */
    virtual void RemoveSlot(int index, RyujinConstants::Slots type = RyujinConstants::Slots::GIF) = 0;
    /**
     * Prints all the slots onto standard output
     */
    virtual void PrintAll() = 0;

    /**
     * Method to return a list of selected slot type
     * @param type Desired slot type to get
     * @return Return the list of the selected slot type
     */
    virtual slot_type GetSlotsByType(RyujinConstants::Slots type = RyujinConstants::Slots::GIF) = 0;

private:
    /**
     * Update the selected slot type into path + file (selected slot type)
     * @param type Selected slot type
     */
    virtual void UpdateSlot(RyujinConstants::Slots type) = 0;
    /**
     * Prints the selected slot type onto standard output and prints the title as header
     * @param type Selected slot type
     * @param title Header to print to standard output
     */
    virtual void PrintSlots(RyujinConstants::Slots type, const std::string &title) = 0;
    /**
     * Method that initializes a slot property with the data from the specified file_path
     * @param file_path Full file path to read in order to initialize slot property
     * @param array_reference Reference to slot property to update
     */
    virtual void ReadSlots(std::string file_path, slot_type &array_reference) = 0;
};


#endif // RYUJINIII_MEMORY_SLOTS_STORE_BASE_H
