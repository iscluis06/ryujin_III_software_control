#include "commands/end_upload_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mocks/libusb_wrapper_mock.h"

class EndUploadCommandTest : public testing::Test {};

TEST_F(EndUploadCommandTest, ExecuteSuccess) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    EndUploadCommand end_upload_command(wrapper_mock);
    std::vector<unsigned char> default_array{65, 0};
    std::vector<unsigned char> valid_response = {0xec, 0x73};
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([valid_response](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(end_upload_command.Execute(), true);
}

TEST_F(EndUploadCommandTest, ExecuteFail) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    EndUploadCommand end_upload_command(wrapper_mock);
    std::vector<unsigned char> default_array{65, 0};
    std::vector<unsigned char> valid_response = {0xec, 0x73};
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(end_upload_command.Execute(), false);
}

TEST_F(EndUploadCommandTest, InvalidResponse) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    EndUploadCommand end_upload_command(wrapper_mock);
    std::vector<unsigned char> default_array{65, 0};
    std::vector<unsigned char> valid_response = {0xec, 0x73};
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([default_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(end_upload_command.Execute(), false);
}
