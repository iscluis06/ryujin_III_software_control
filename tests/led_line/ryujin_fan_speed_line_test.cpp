#include "led_line/ryujin_fan_speed_line.h"

#include <gtest/gtest.h>

#include "stores/hardware_status_store_mock.h"

class RyujinFanSpeedLineTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        mock = std::make_shared<HardwareStatusStoreMock>();
        default_value = 5000;
        default_title = "Fan Speed";
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<HardwareStatusStoreMock> mock;
    static int default_value;
    static std::string default_title;
};
std::shared_ptr<HardwareStatusStoreMock> RyujinFanSpeedLineTest::mock;
int RyujinFanSpeedLineTest::default_value;
std::string RyujinFanSpeedLineTest::default_title;

TEST_F(RyujinFanSpeedLineTest, GetLineSuccess) {
    EXPECT_CALL(*(mock.get()), GetFanSpeed).WillRepeatedly(testing::Return(default_value));
    RyujinFanSpeedLine ryujin_fan_speed_line(mock);
    EXPECT_EQ(ryujin_fan_speed_line.GetLine(), std::to_string(default_value).substr(0, 5).append(" rpm"));
}

TEST_F(RyujinFanSpeedLineTest, GetLineFail) {
    EXPECT_CALL(*(mock.get()), GetFanSpeed).WillRepeatedly(testing::Return(0));
    RyujinFanSpeedLine ryujin_fan_speed_line(mock);
    EXPECT_NE(ryujin_fan_speed_line.GetLine(), std::to_string(default_value).substr(0, 5).append(" rpm"));
}

TEST_F(RyujinFanSpeedLineTest, GetTitleSuccess) {
    RyujinFanSpeedLine ryujin_fan_speed_line(mock);
    EXPECT_EQ(ryujin_fan_speed_line.GetTitle(), this->default_title);
}

TEST_F(RyujinFanSpeedLineTest, GetTitleFail) {
    RyujinFanSpeedLine ryujin_fan_speed_line(mock);
    EXPECT_NE(ryujin_fan_speed_line.GetTitle(), "");
}
