#include "commands/end_upload_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class EndUploadCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
        valid_response = {0xec, 0x73};
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
    static std::vector<unsigned char> valid_response;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> EndUploadCommandTest::mock;
std::vector<unsigned char> EndUploadCommandTest::default_array;
std::vector<unsigned char> EndUploadCommandTest::valid_response;

TEST_F(EndUploadCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EndUploadCommand end_upload_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(end_upload_command.Execute(), true);
}

TEST_F(EndUploadCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EndUploadCommand end_upload_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(end_upload_command.Execute(), false);
}

TEST_F(EndUploadCommandTest, InvalidResponse) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EndUploadCommand end_upload_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(end_upload_command.Execute(), false);
}
