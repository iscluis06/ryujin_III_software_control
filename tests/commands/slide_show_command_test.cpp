#include "commands/slide_show_command.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SlideShowCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SlideShowCommandTest::mock;
std::vector<unsigned char> SlideShowCommandTest::default_array;

TEST_F(SlideShowCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SlideShowCommand slide_show_command(mock, std::vector<int>{1, 2});
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_EQ(slide_show_command.Execute(), true);
}

TEST_F(SlideShowCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SlideShowCommand slide_show_command(mock, std::vector<int>{1, 2});
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(slide_show_command.Execute(), false);
}
