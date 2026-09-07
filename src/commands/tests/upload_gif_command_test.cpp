#include "commands/upload_gif_command.h"
#include <gtest/gtest.h>
#include "file_handle_mock.h"
#include "libusb_wrapper_mock.h"

class UploadGifCommandTest : public testing::Test {};

TEST_F(UploadGifCommandTest, ExecuteSuccess) {
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock =
            std::make_shared<testing::NiceMock<FileHandleMock>>();
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    file_handle_mock->SetIterations(1);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[65]));
    file_handle_mock->SetSize(65);
    UploadGifCommand upload_gif_command(wrapper_mock, file_handle_mock);
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillOnce(testing::Return(true));
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillOnce(testing::Return(true));
    EXPECT_EQ(upload_gif_command.Execute(), true);
}

TEST_F(UploadGifCommandTest, ExecuteFail) {
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock =
            std::make_shared<testing::NiceMock<FileHandleMock>>();
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    file_handle_mock->SetIterations(1);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[65]));
    file_handle_mock->SetSize(65);
    UploadGifCommand upload_gif_command(wrapper_mock, file_handle_mock);
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillOnce(testing::Return(false));
    EXPECT_EQ(upload_gif_command.Execute(), false);
}
