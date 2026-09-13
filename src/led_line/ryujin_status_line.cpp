#include "led_line/ryujin_status_line.h"

RyujinStatusLine::RyujinStatusLine(std::shared_ptr<HardwareStatusStore> store) : store_(store) {}
std::shared_ptr<HardwareStatusStore> RyujinStatusLine::GetStore() { return this->store_; }
