#ifndef RYUJINIII_MEMORY_SLOTS_STORE_MOCK_H
#define RYUJINIII_MEMORY_SLOTS_STORE_MOCK_H

#include <gmock/gmock.h>

#include "stores/memory_slots_store.h"

class MemorySlotsStoreMock : public MemorySlotsStore {
public:
    MemorySlotsStoreMock(const std::string &path) : MemorySlotsStore(path) {}
    ~MemorySlotsStoreMock() override = default;
    MOCK_METHOD(void, UpdateSlots, (), (override));
    MOCK_METHOD(void, WriteSlot, (int index, const std::string &path, SlotType type), (override));
    MOCK_METHOD(void, RemoveSlot, (int index, SlotType type), (override));
    MOCK_METHOD(void, PrintAll, (), (override));
};

#endif // RYUJINIII_MEMORY_SLOTS_STORE_MOCK_H
