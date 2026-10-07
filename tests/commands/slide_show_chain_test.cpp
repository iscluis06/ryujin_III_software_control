#include "commands/slide_show_chain.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SlideShowChainTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::vector<unsigned char> default_array;
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SlideShowChainTest::mock;
std::vector<unsigned char> SlideShowChainTest::default_array;

TEST_F(SlideShowChainTest, ExecuteSuccessFirstTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(3).WillRepeatedly(testing::Return(default_array));
    SlideShowChain slide_show_chain{mock, std::vector<int>{1, 2}};

    EXPECT_CALL(*(mock.get()), SendInterrupt).Times(6).WillRepeatedly(testing::Return(true));

    EXPECT_EQ(slide_show_chain.Execute(), true);
}

TEST_F(SlideShowChainTest, ExecuteSuccessSecondTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(3).WillRepeatedly(testing::Return(default_array));
    SlideShowChain slide_show_chain{mock, std::vector<int>{1, 2}};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(slide_show_chain.Execute(), true);
}

TEST_F(SlideShowChainTest, ExecuteSuccessThirdTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(3).WillRepeatedly(testing::Return(default_array));
    SlideShowChain slide_show_chain{mock, std::vector<int>{1, 2}};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(slide_show_chain.Execute(), true);
}


TEST_F(SlideShowChainTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(3).WillRepeatedly(testing::Return(default_array));
    SlideShowChain slide_show_chain{mock, std::vector<int>{1, 2}};


    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));

    EXPECT_EQ(slide_show_chain.Execute(), false);
}
