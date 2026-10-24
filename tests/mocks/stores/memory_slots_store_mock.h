#ifndef RYUJINIII_MEMORY_SLOTS_STORE_MOCK_H
#define RYUJINIII_MEMORY_SLOTS_STORE_MOCK_H

#include <gmock/gmock.h>

#include "ryujin/ryujin_constants.h"
#include "stores/memory_slots_store.h"

class MemorySlotsStoreMock : public MemorySlotsStoreBase {
public:
    MemorySlotsStoreMock() = default;
    ~MemorySlotsStoreMock() override = default;
    MOCK_METHOD(void, UpdateSlots, (), (override));
    MOCK_METHOD(void, WriteSlot, (int index, const std::string &path, RyujinConstants::Slots type), (override));
    MOCK_METHOD(void, RemoveSlot, (int index, RyujinConstants::Slots type), (override));
    MOCK_METHOD(void, PrintAll, (), (override));
    MOCK_METHOD(slot_type, GetSlotsByType, (RyujinConstants::Slots), (override));

private:
    MOCK_METHOD(void, UpdateSlot, (RyujinConstants::Slots), (override));
    MOCK_METHOD(void, PrintSlots, (RyujinConstants::Slots, const std::string &), (override));
    MOCK_METHOD(void, ReadSlots, (std::string file_path, slot_type &array_reference), (override));
};

#endif // RYUJINIII_MEMORY_SLOTS_STORE_MOCK_H
