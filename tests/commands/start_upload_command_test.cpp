#include "commands/start_upload_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class StartUploadCommandTest : public testing::Test {};

TEST_F(StartUploadCommandTest, ExecuteSuccess) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    StartUploadCommand start_upload_command(wrapper_mock);
    std::vector<unsigned char> default_array(65, 0);
    std::vector<unsigned char> valid_response = {0xec, 0x73};
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([valid_response](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(start_upload_command.Execute(), true);
}

TEST_F(StartUploadCommandTest, ExecuteFail) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    std::vector<unsigned char> size = {0x00, 0xff, 0x1f};
    StartUploadCommand start_upload_command(wrapper_mock);
    std::vector<unsigned char> default_array(65, 0);
    std::vector<unsigned char> valid_response = {0xec, 0x73};
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(start_upload_command.Execute(), false);
}

TEST_F(StartUploadCommandTest, InvalidResponse) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    std::vector<unsigned char> size = {0x00, 0xff, 0x1f};
    StartUploadCommand start_upload_command(wrapper_mock);
    std::vector<unsigned char> default_array(65, 0);
    std::vector<unsigned char> valid_response = {0xec, 0x73};
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([default_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(start_upload_command.Execute(), false);
}
