#ifndef RYUJINIII_RYUJIN_STATUS_LINE_H
#define RYUJINIII_RYUJIN_STATUS_LINE_H

#include <memory>
#include "stores/hardware_status_store.h"

class RyujinStatusLine {
public:
    RyujinStatusLine(std::shared_ptr<HardwareStatusStore> store);
    std::shared_ptr<HardwareStatusStore> GetStore();

private:
    std::shared_ptr<HardwareStatusStore> store_;
};

#endif // RYUJINIII_RYUJIN_STATUS_LINE_H
