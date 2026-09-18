#include "led_line/led_line_factory.h"


#include <gtest/gtest.h>

#include "led_line/amd_core_line.h"
#include "led_line/git_last_commiter_line.h"
#include "led_line/ryujin_fan_speed_line.h"
#include "led_line/ryujin_liquid_temp_line.h"
#include "led_line/ryujin_pump_speed_line.h"
#include "stores/hardware_status_store_mock.h"

class LedLineFactoryTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        mock = std::make_shared<HardwareStatusStoreMock>();
        git_test_path = "test path";
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<HardwareStatusStoreMock> mock;
    static std::string git_test_path;
};

std::shared_ptr<HardwareStatusStoreMock> LedLineFactoryTest::mock;
std::string LedLineFactoryTest::git_test_path;

TEST_F(LedLineFactoryTest, FactorySuccessLiquidTemp) {
    LedLineFactory led_line_factory(mock);
    RyujinLiquidTempLine ryujin_liquid_temp_line(mock);
    EXPECT_EQ(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::RYUJIN_LIQUID_TEMP)->GetClassName(),
              ryujin_liquid_temp_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactoryFailLiquidTemp) {
    LedLineFactory led_line_factory(mock);
    RyujinLiquidTempLine ryujin_liquid_temp_line(mock);
    EXPECT_NE(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::AMD_CORE_TEMP)->GetClassName(),
              ryujin_liquid_temp_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactorySuccessPumpSpeed) {
    LedLineFactory led_line_factory(mock);
    RyujinPumpSpeedLine ryujin_pump_speed_line(mock);
    EXPECT_EQ(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::RYUJIN_PUMP_SPEED)->GetClassName(),
              ryujin_pump_speed_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactoryFailPumpSpeed) {
    LedLineFactory led_line_factory(mock);
    RyujinPumpSpeedLine ryujin_pump_speed_line(mock);
    EXPECT_NE(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::AMD_CORE_TEMP)->GetClassName(),
              ryujin_pump_speed_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactorySuccessFanSpeed) {
    LedLineFactory led_line_factory(mock);
    RyujinFanSpeedLine ryujin_fan_speed_line(mock);
    EXPECT_EQ(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::RYUJIN_FAN_SPEED)->GetClassName(),
              ryujin_fan_speed_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactoryFailFanSpeed) {
    LedLineFactory led_line_factory(mock);
    RyujinFanSpeedLine ryujin_fan_speed_line(mock);
    EXPECT_NE(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::AMD_CORE_TEMP)->GetClassName(),
              ryujin_fan_speed_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactorySuccessAmdCore) {
    LedLineFactory led_line_factory(mock);
    AmdCoreLine amd_core_line;
    EXPECT_EQ(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::AMD_CORE_TEMP)->GetClassName(),
              amd_core_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactoryFailAmdCore) {
    LedLineFactory led_line_factory(mock);
    AmdCoreLine amd_core_line;
    EXPECT_NE(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::RYUJIN_FAN_SPEED)->GetClassName(),
              amd_core_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactorySuccessGitCommiter) {
    LedLineFactory led_line_factory(mock);
    led_line_factory.SetGitPath(git_test_path);
    GitLastCommiterLine git_last_commiter_line(git_test_path);
    EXPECT_EQ(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::GIT_LAST_COMMITER)->GetClassName(),
              git_last_commiter_line.GetClassName());
}

TEST_F(LedLineFactoryTest, FactoryFailGitCommiter) {
    LedLineFactory led_line_factory(mock);
    led_line_factory.SetGitPath(git_test_path);
    GitLastCommiterLine git_last_commiter_line(git_test_path);
    EXPECT_NE(led_line_factory.GetLedLine(LedLineFactory::LedLineImplementations::RYUJIN_FAN_SPEED)->GetClassName(),
              git_last_commiter_line.GetClassName());
}
