#include "commands/select_jpeg_command.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SelectJpegCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SelectJpegCommandTest::mock;
std::vector<unsigned char> SelectJpegCommandTest::default_array;

TEST_F(SelectJpegCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SelectJpegCommand select_jpeg_command(mock, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_EQ(select_jpeg_command.Execute(), true);
}

TEST_F(SelectJpegCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SelectJpegCommand select_jpeg_command(mock, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(select_jpeg_command.Execute(), false);
}
