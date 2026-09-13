#include "led_line/ryujin_liquid_temp_line.h"

#include <bits/this_thread_sleep.h>
#include <gtest/gtest.h>

class RyujinLiquidTempLineTest : public testing::Test {};

TEST_F(RyujinLiquidTempLineTest, Test1) {
    RyujinLiquidTempLine temp;
    while (1) {
        std::string value = temp.GetLine();
        std::cout << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // std::string value2 = temp.GetLine();
        // std::cout << value2 << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // std::string value3 = temp.GetLine();
        // std::cout << value3 << std::endl;
    }
}
