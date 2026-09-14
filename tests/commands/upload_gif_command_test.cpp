#include "commands/upload_gif_command.h"
#include <gtest/gtest.h>
#include "file_handle_mock.h"
#include "libusb_wrapper_mock.h"

class UploadGifCommandTest : public testing::Test {
protected:
    void SetUp() {
        file_handle_mock = std::make_shared<testing::NiceMock<FileHandleMock>>();
        wrapper_mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    }
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock;
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock;
    const int kDefaultIterations = 1;
    const int kDefaultBufferSize = 65;
};

TEST_F(UploadGifCommandTest, ExecuteSuccess) {
    this->file_handle_mock->SetIterations(this->kDefaultIterations);
    this->file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[this->kDefaultBufferSize]));
    this->file_handle_mock->SetSize(this->kDefaultBufferSize);
    UploadGifCommand upload_gif_command(this->wrapper_mock, this->file_handle_mock);
    EXPECT_CALL(*(this->wrapper_mock.get()), SendInterrupt).WillOnce(testing::Return(true));
    EXPECT_CALL(*(this->wrapper_mock.get()), SendBulk).WillOnce(testing::Return(true));
    EXPECT_EQ(upload_gif_command.Execute(), true);
}

TEST_F(UploadGifCommandTest, ExecuteFail) {
    this->file_handle_mock->SetIterations(this->kDefaultIterations);
    this->file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[this->kDefaultBufferSize]));
    this->file_handle_mock->SetSize(this->kDefaultBufferSize);
    UploadGifCommand upload_gif_command(this->wrapper_mock, file_handle_mock);
    EXPECT_CALL(*(this->wrapper_mock.get()), SendBulk).WillOnce(testing::Return(false));
    EXPECT_EQ(upload_gif_command.Execute(), false);
}
