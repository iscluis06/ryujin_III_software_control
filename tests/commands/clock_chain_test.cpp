#include <gtest/gtest.h>

#include "commands/clock_chain.h"
#include "libusb_wrapper_mock.h"

class ClockChainTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::vector<unsigned char> default_array;
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> ClockChainTest::mock;
std::vector<unsigned char> ClockChainTest::default_array;

TEST_F(ClockChainTest, ExecuteSuccessFirstTry) {
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    ClockChain clock_chain{mock};

    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(clock_chain.Execute(), true);
}

TEST_F(ClockChainTest, ExecuteSuccessSecondTry) {
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    ClockChain clock_chain{mock};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(clock_chain.Execute(), true);
}

TEST_F(ClockChainTest, ExecuteSuccessThirdTry) {
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    ClockChain clock_chain{mock};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(clock_chain.Execute(), true);
}

TEST_F(ClockChainTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    ClockChain clock_chain{mock};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false));

    EXPECT_EQ(clock_chain.Execute(), false);
}
