#include "byte_utils.h"
#include <gtest/gtest.h>

class ByteUtilsTest : public testing::Test {};

TEST_F(ByteUtilsTest, TransformHexStringToDecimalSuccess) {
    ByteUtils utils;
    std::string hex_string1 = "0545";
    int decimal_value1 = 1349;
    int result = utils.GetDecimalValueFromHexString(hex_string1);
    EXPECT_EQ(result, decimal_value1);
    std::string hex_string2 = "0305";
    int decimal_value2 = 773;
    result = utils.GetDecimalValueFromHexString(hex_string2);
    EXPECT_EQ(result, decimal_value2);
}
