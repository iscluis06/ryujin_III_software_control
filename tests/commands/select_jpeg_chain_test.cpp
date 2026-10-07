#include "commands/select_jpeg_chain.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SelectJpegChainTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::vector<unsigned char> default_array;
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SelectJpegChainTest::mock;
std::vector<unsigned char> SelectJpegChainTest::default_array;

TEST_F(SelectJpegChainTest, ExecuteSuccessFirstTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SelectJpegChain select_jpeg_chain{mock, 1};

    EXPECT_CALL(*(mock.get()), SendInterrupt).Times(8).WillRepeatedly(testing::Return(true));

    EXPECT_EQ(select_jpeg_chain.Execute(), true);
}

TEST_F(SelectJpegChainTest, ExecuteSuccessSecondTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SelectJpegChain select_jpeg_chain{mock, 1};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(select_jpeg_chain.Execute(), true);
}

TEST_F(SelectJpegChainTest, ExecuteSuccessThirdTry) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SelectJpegChain select_jpeg_chain{mock, 1};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true));

    EXPECT_EQ(select_jpeg_chain.Execute(), true);
}


TEST_F(SelectJpegChainTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(4).WillRepeatedly(testing::Return(default_array));
    SelectJpegChain select_jpeg_chain{mock, 1};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false));

    EXPECT_EQ(select_jpeg_chain.Execute(), false);
}
