#include "commands/select_memory_space_jpeg_command.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SelectMemorySpaceJpegCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
        valid_response = {0xec, 0x72};
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
    static std::vector<unsigned char> valid_response;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SelectMemorySpaceJpegCommandTest::mock;
std::vector<unsigned char> SelectMemorySpaceJpegCommandTest::default_array;
std::vector<unsigned char> SelectMemorySpaceJpegCommandTest::valid_response;

TEST_F(SelectMemorySpaceJpegCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SelectMemorySpaceJPEGCommand select_memory_space_jpeg_command(mock, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(select_memory_space_jpeg_command.Execute(), true);
}

TEST_F(SelectMemorySpaceJpegCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SelectMemorySpaceJPEGCommand select_memory_space_jpeg_command(mock, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(select_memory_space_jpeg_command.Execute(), false);
}
