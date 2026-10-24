#include "commands/slide_show_jpeg_command.h"
#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SlideShowJpegCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SlideShowJpegCommandTest::mock;
std::vector<unsigned char> SlideShowJpegCommandTest::default_array;

TEST_F(SlideShowJpegCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SlideShowJpegCommand slide_show_jpeg_command(mock, std::vector<int>{1});
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_EQ(slide_show_jpeg_command.Execute(), true);
}

TEST_F(SlideShowJpegCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SlideShowJpegCommand slide_show_jpeg_command(mock, std::vector<int>{1});
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(slide_show_jpeg_command.Execute(), false);
}
