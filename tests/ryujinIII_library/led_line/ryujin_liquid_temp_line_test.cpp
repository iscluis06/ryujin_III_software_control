#include "led_line/ryujin_liquid_temp_line.h"

#include <bits/this_thread_sleep.h>
#include <gtest/gtest.h>

#include "stores/hardware_status_store_mock.h"

class RyujinLiquidTempLineTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        mock = std::make_shared<HardwareStatusStoreMock>();
        default_value = 32000;
        default_title = "Liquid Temp";
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<HardwareStatusStoreMock> mock;
    static float default_value;
    static std::string default_title;
};
std::shared_ptr<HardwareStatusStoreMock> RyujinLiquidTempLineTest::mock;
float RyujinLiquidTempLineTest::default_value;
std::string RyujinLiquidTempLineTest::default_title;

TEST_F(RyujinLiquidTempLineTest, GetLineSuccess) {
    EXPECT_CALL(*(mock.get()), GetLiquidTemp).WillRepeatedly(testing::Return(default_value));
    RyujinLiquidTempLine ryujin_liquid_temp_line(mock);
    EXPECT_EQ(ryujin_liquid_temp_line.GetLine(), std::to_string(default_value).substr(0, 5).append("\u2103"));
}

TEST_F(RyujinLiquidTempLineTest, GetLineFail) {
    EXPECT_CALL(*(mock.get()), GetLiquidTemp).WillRepeatedly(testing::Return(0));
    RyujinLiquidTempLine ryujin_liquid_temp_line(mock);
    EXPECT_NE(ryujin_liquid_temp_line.GetLine(), std::to_string(default_value).substr(0, 5).append("\u2103"));
}

TEST_F(RyujinLiquidTempLineTest, GetTitleSuccess) {
    RyujinLiquidTempLine ryujin_liquid_temp_line(mock);
    EXPECT_EQ(ryujin_liquid_temp_line.GetTitle(), this->default_title);
}

TEST_F(RyujinLiquidTempLineTest, GetTitleFail) {
    RyujinLiquidTempLine ryujin_liquid_temp_line(mock);
    EXPECT_NE(ryujin_liquid_temp_line.GetTitle(), "");
}
