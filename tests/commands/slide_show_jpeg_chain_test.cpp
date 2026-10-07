#include "commands/slide_show_jpeg_chain.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SlideShowJpegChainTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::vector<unsigned char> default_array;
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SlideShowJpegChainTest::mock;
std::vector<unsigned char> SlideShowJpegChainTest::default_array;

TEST_F(SlideShowJpegChainTest, ExecuteSuccessFirstTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SlideShowJpegChain slide_show_jpeg_chain{mock, std::vector<int>{1, 2}};

    EXPECT_CALL(*(mock.get()), SendInterrupt).Times(6).WillRepeatedly(testing::Return(true));

    EXPECT_EQ(slide_show_jpeg_chain.Execute(), true);
}

TEST_F(SlideShowJpegChainTest, ExecuteSuccessSecondTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SlideShowJpegChain slide_show_jpeg_chain{mock, std::vector<int>{1, 2}};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(slide_show_jpeg_chain.Execute(), true);
}

TEST_F(SlideShowJpegChainTest, ExecuteSuccessThirdTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SlideShowJpegChain slide_show_jpeg_chain{mock, std::vector<int>{1, 2}};

    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(slide_show_jpeg_chain.Execute(), true);
}


TEST_F(SlideShowJpegChainTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SlideShowJpegChain slide_show_jpeg_chain{mock, std::vector<int>{1, 2}};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false));

    EXPECT_EQ(slide_show_jpeg_chain.Execute(), false);
}
