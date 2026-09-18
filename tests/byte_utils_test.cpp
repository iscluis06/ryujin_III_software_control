#include "byte_utils.h"
#include <gtest/gtest.h>

class ByteUtilsTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        hex_string1 = "0545";
        decimal_value1 = 1349;
        hex_string2 = "0305";
        decimal_value2 = 773;
        decimal_value3 = 774;
        hex_value = 0xec;
        hex_value_str = "ec";
        ascii_value_array = {0x70, 0x65};
        ascii_value_str = "pe";
        ascii_value_array_fail = {0x70, 0x66};
    }
    static std::string hex_string1;
    static int decimal_value1;
    static std::string hex_string2;
    static int decimal_value2;
    static int decimal_value3;
    static unsigned char hex_value;
    static std::string hex_value_str;
    static std::vector<unsigned char> ascii_value_array;
    static std::vector<unsigned char> ascii_value_array_fail;
    static std::string ascii_value_str;
};

std::string ByteUtilsTest::hex_string1;
int ByteUtilsTest::decimal_value1;
std::string ByteUtilsTest::hex_string2;
int ByteUtilsTest::decimal_value2;
int ByteUtilsTest::decimal_value3;
unsigned char ByteUtilsTest::hex_value;
std::string ByteUtilsTest::hex_value_str;
std::vector<unsigned char> ByteUtilsTest::ascii_value_array;
std::vector<unsigned char> ByteUtilsTest::ascii_value_array_fail;
std::string ByteUtilsTest::ascii_value_str;

TEST_F(ByteUtilsTest, TransformHexStringToDecimalSuccess) {
    ByteUtils utils;
    int result = utils.GetDecimalValueFromHexString(hex_string1);
    EXPECT_EQ(result, decimal_value1);
    result = utils.GetDecimalValueFromHexString(hex_string2);
    EXPECT_EQ(result, decimal_value2);
}

TEST_F(ByteUtilsTest, TransformHexStringToDecimalFail) {
    ByteUtils utils;
    int result = utils.GetDecimalValueFromHexString(hex_string1);
    EXPECT_EQ(result, decimal_value1);
    result = utils.GetDecimalValueFromHexString(hex_string2);
    EXPECT_NE(result, decimal_value3);
}

TEST_F(ByteUtilsTest, GetHexRepresentationSuccess) {
    ByteUtils utils;
    auto result = utils.GetHexRepresentation(hex_value);
    EXPECT_EQ(result, hex_value_str);
}

TEST_F(ByteUtilsTest, GetHexRepresentationFail) {
    ByteUtils utils;
    auto result = utils.GetHexRepresentation(hex_value);
    EXPECT_NE(result, ascii_value_str);
}

TEST_F(ByteUtilsTest, ReturnASCIISuccess) {
    ByteUtils utils;
    auto result = utils.ReturnASCII(ascii_value_str);
    EXPECT_EQ(result, ascii_value_array);
}

TEST_F(ByteUtilsTest, ReturnASCIIFail) {
    ByteUtils utils;
    auto result = utils.ReturnASCII(ascii_value_str);
    EXPECT_NE(result, ascii_value_array_fail);
}
