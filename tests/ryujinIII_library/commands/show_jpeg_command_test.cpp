#include "commands/show_jpeg_command.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class ShowJpegCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> ShowJpegCommandTest::mock;
std::vector<unsigned char> ShowJpegCommandTest::default_array;

TEST_F(ShowJpegCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    ShowJpegCommand show_jpeg_command(mock, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_EQ(show_jpeg_command.Execute(), true);
}

TEST_F(ShowJpegCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    ShowJpegCommand show_jpeg_command(mock, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(show_jpeg_command.Execute(), false);
}
