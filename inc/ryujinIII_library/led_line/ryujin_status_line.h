#ifndef RYUJINIII_RYUJIN_STATUS_LINE_H
#define RYUJINIII_RYUJIN_STATUS_LINE_H

#include <memory>
#include "stores/hardware_status_store.h"

/**
 * Abstract class to encapsulate ryujin hardware store data
 */
class RyujinStatusLine {
public:
    /**
     * Constructor which also initialize store property
     * @param store Reference to hardware status store
     */
    RyujinStatusLine(std::shared_ptr<HardwareStatusStore> store);
    /**
     * Returns a reference to hardware status store
     * @return A reference to store_ property
     */
    std::shared_ptr<HardwareStatusStore> GetStore();

private:
    /**
     * Reference to hardware status store
     */
    std::shared_ptr<HardwareStatusStore> store_;
};

#endif // RYUJINIII_RYUJIN_STATUS_LINE_H
