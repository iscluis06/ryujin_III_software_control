#include "led_line/ryujin_pump_speed_line.h"
#include <gtest/gtest.h>
#include "stores/hardware_status_store_mock.h"


class RyujinPumpSpeedLineTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        mock = std::make_shared<HardwareStatusStoreMock>();
        default_value = 56000;
        default_title = "Pump Speed";
    }
    static int default_value;
    static std::string default_title;
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<HardwareStatusStoreMock> mock;
};

int RyujinPumpSpeedLineTest::default_value;
std::string RyujinPumpSpeedLineTest::default_title;
std::shared_ptr<HardwareStatusStoreMock> RyujinPumpSpeedLineTest::mock;

TEST_F(RyujinPumpSpeedLineTest, GetLineSuccess) {
    EXPECT_CALL(*(mock.get()), GetPumpSpeed).WillRepeatedly(testing::Return(default_value));
    RyujinPumpSpeedLine ryujin_pump_speed_line(mock);
    EXPECT_EQ(ryujin_pump_speed_line.GetLine(), std::to_string(default_value).substr(0, 5).append(" rpm"));
}

TEST_F(RyujinPumpSpeedLineTest, GetLineFail) {
    EXPECT_CALL(*(mock.get()), GetPumpSpeed).WillRepeatedly(testing::Return(0));
    RyujinPumpSpeedLine ryujin_pump_speed_line(mock);
    EXPECT_NE(ryujin_pump_speed_line.GetLine(), std::to_string(default_value).substr(0, 5).append(" rpm"));
}

TEST_F(RyujinPumpSpeedLineTest, GetTitleSuccess) {
    RyujinPumpSpeedLine ryujin_pump_speed_line(mock);
    EXPECT_EQ(ryujin_pump_speed_line.GetTitle(), this->default_title);
}

TEST_F(RyujinPumpSpeedLineTest, GetTitleFail) {
    RyujinPumpSpeedLine ryujin_pump_speed_line(mock);
    EXPECT_NE(ryujin_pump_speed_line.GetTitle(), "");
}
