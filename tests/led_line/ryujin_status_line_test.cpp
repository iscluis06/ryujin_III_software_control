#include "led_line/ryujin_status_line.h"
#include <gtest/gtest.h>

#include "stores/hardware_status_store_mock.h"

class RyujinStatusLineTest : public testing::Test {
public:
    static void SetUpTestSuite() { mock = std::make_shared<HardwareStatusStoreMock>(); }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<HardwareStatusStoreMock> mock;
};

std::shared_ptr<HardwareStatusStoreMock> RyujinStatusLineTest::mock;

TEST_F(RyujinStatusLineTest, GetStoreEqual) {
    RyujinStatusLine ryujin_status_line(mock);
    EXPECT_EQ(mock, ryujin_status_line.GetStore());
}

TEST_F(RyujinStatusLineTest, GetStoreNull) {
    RyujinStatusLine ryujin_status_line(nullptr);
    EXPECT_EQ(nullptr, ryujin_status_line.GetStore());
}
