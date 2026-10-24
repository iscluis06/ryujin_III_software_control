#include "commands/upload_gif_command.h"
#include <gtest/gtest.h>
#include "file_handle_mock.h"
#include "libusb_wrapper_mock.h"

class UploadGifCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        file_handle_mock = std::make_shared<testing::NiceMock<FileHandleMock>>();
        wrapper_mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    }
    static void TearDownTestSuite() {
        file_handle_mock.reset();
        wrapper_mock.reset();
    }
    static std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock;
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock;
    static constexpr int kDefaultIterations = 1;
    static constexpr int kDefaultBufferSize = 65;
};

std::shared_ptr<testing::NiceMock<FileHandleMock>> UploadGifCommandTest::file_handle_mock;
std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> UploadGifCommandTest::wrapper_mock;

TEST_F(UploadGifCommandTest, ExecuteSuccess) {
    file_handle_mock->SetIterations(kDefaultIterations);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[kDefaultBufferSize]));
    file_handle_mock->SetSize(kDefaultBufferSize);
    UploadGifCommand upload_gif_command(wrapper_mock, file_handle_mock);
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillOnce(testing::Return(true));
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillOnce(testing::Return(true));
    EXPECT_EQ(upload_gif_command.Execute(), true);
}

TEST_F(UploadGifCommandTest, ExecuteFail) {
    file_handle_mock->SetIterations(kDefaultIterations);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[kDefaultBufferSize]));
    file_handle_mock->SetSize(kDefaultBufferSize);
    UploadGifCommand upload_gif_command(wrapper_mock, file_handle_mock);
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillOnce(testing::Return(false));
    EXPECT_EQ(upload_gif_command.Execute(), false);
}
