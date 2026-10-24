#include <gtest/gtest.h>

#include "led_line/amd_core_line_mock.h"

class AmdCoreLineTest : public testing::Test {};

TEST_F(AmdCoreLineTest, GetLineSuccess) {
    testing::NiceMock<AmdCoreLineMock> amd_core_line;
    std::string expected_temp = "38254";
    std::string final_temp = std::to_string(std::stoi(expected_temp) / 1000.0f).substr(0, 5).append("\u2103");
    EXPECT_CALL(amd_core_line, IsHardwareNameAvailable).WillOnce(testing::Return(true));
    EXPECT_CALL(amd_core_line, GetInputValue()).WillOnce(testing::Return(expected_temp));
    std::string result = amd_core_line.GetLine();
    EXPECT_GT(result.length(), 0);
    EXPECT_EQ(result, final_temp);
}

TEST_F(AmdCoreLineTest, GetLineFail) {
    testing::NiceMock<AmdCoreLineMock> amd_core_line;
    std::string expected_temp = "38254";
    EXPECT_CALL(amd_core_line, IsHardwareNameAvailable).WillOnce(testing::Return(false));
    std::string result = amd_core_line.GetLine();
    EXPECT_EQ(result.length(), 0);
    EXPECT_EQ(result, "");
}

TEST_F(AmdCoreLineTest, TransformValueSuccess) {
    testing::NiceMock<AmdCoreLineMock> amd_core_line;
    std::string expected_temp = "38254";
    std::string final_temp = std::to_string(std::stoi(expected_temp) / 1000.0f).substr(0, 5).append("\u2103");
    std::string result = amd_core_line.TransformValue(expected_temp);
    EXPECT_EQ(result.length(), final_temp.length());
    EXPECT_EQ(result, final_temp);
}

TEST_F(AmdCoreLineTest, TransformValueFail) {
    testing::NiceMock<AmdCoreLineMock> amd_core_line;
    std::string fail_string = "ABCDEFG";
    std::string result = amd_core_line.TransformValue(fail_string);
    EXPECT_EQ(result.length(), 0);
    EXPECT_EQ(result, "");
}

TEST_F(AmdCoreLineTest, TransformValueEmpty) {
    testing::NiceMock<AmdCoreLineMock> amd_core_line;
    std::string empty_string = "";
    std::string result = amd_core_line.TransformValue(empty_string);
    EXPECT_EQ(result.length(), 0);
    EXPECT_EQ(result, empty_string);
}
