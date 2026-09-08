#include "commands/upload_chain.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../mocks/file_handle_mock.h"
#include "../mocks/libusb_wrapper_mock.h"
#include "../mocks/transform_tool_mock.h"

class UploadChainTest : public testing::Test {};

TEST_F(UploadChainTest, ExecuteSuccessFirstTry) {
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock =
            std::make_shared<testing::NiceMock<FileHandleMock>>();
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    std::shared_ptr<testing::NiceMock<TransformToolMock>> transform_tool_mock =
            std::make_shared<testing::NiceMock<TransformToolMock>>();
    file_handle_mock->SetIterations(1);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[65]));
    file_handle_mock->SetSize(65);
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    std::vector<unsigned char> default_array(65, 0);
    std::vector<unsigned char> transaction_command = {0xec, 0x71};
    std::vector<unsigned char> start_transaction_command = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
    std::vector<unsigned char> select_memory_command = {0xec, 0x72};
    std::vector<unsigned char> start_upload_command = {0xec, 0x73};
    std::vector<unsigned char> reported_size_command = {0xec, 0x7f, 0x0, 0x0, 0x10};
    std::vector<unsigned char> end_upload_command = {0xec, 0x73};
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Transaction Command
            .WillOnce(testing::Return(default_array)) // Start Transaction Command
            .WillOnce(testing::Return(default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(default_array)) // Start Upload Command
            .WillOnce(testing::Return(default_array)) // Reported Size Command
            .WillOnce(testing::Return(default_array)); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([transaction_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([start_transaction_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([select_memory_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([start_upload_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([reported_size_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([end_upload_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteSuccessSecondTry) {
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock =
            std::make_shared<testing::NiceMock<FileHandleMock>>();
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    std::shared_ptr<testing::NiceMock<TransformToolMock>> transform_tool_mock =
            std::make_shared<testing::NiceMock<TransformToolMock>>();
    file_handle_mock->SetIterations(1);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[65]));
    file_handle_mock->SetSize(65);
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    std::vector<unsigned char> default_array(65, 0);
    std::vector<unsigned char> transaction_command = {0xec, 0x71};
    std::vector<unsigned char> start_transaction_command = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
    std::vector<unsigned char> select_memory_command = {0xec, 0x72};
    std::vector<unsigned char> start_upload_command = {0xec, 0x73};
    std::vector<unsigned char> reported_size_command = {0xec, 0x7f, 0x0, 0x0, 0x10};
    std::vector<unsigned char> end_upload_command = {0xec, 0x73};
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Transaction Command
            .WillOnce(testing::Return(default_array)) // Start Transaction Command
            .WillOnce(testing::Return(default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(default_array)) // Start Upload Command
            .WillOnce(testing::Return(default_array)) // Reported Size Command
            .WillOnce(testing::Return(default_array)); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([transaction_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([start_transaction_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([select_memory_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([start_upload_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([reported_size_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([end_upload_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteSuccessThirdTry) {
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock =
            std::make_shared<testing::NiceMock<FileHandleMock>>();
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    std::shared_ptr<testing::NiceMock<TransformToolMock>> transform_tool_mock =
            std::make_shared<testing::NiceMock<TransformToolMock>>();
    file_handle_mock->SetIterations(1);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[65]));
    file_handle_mock->SetSize(65);
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    std::vector<unsigned char> default_array(65, 0);
    std::vector<unsigned char> transaction_command = {0xec, 0x71};
    std::vector<unsigned char> start_transaction_command = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
    std::vector<unsigned char> select_memory_command = {0xec, 0x72};
    std::vector<unsigned char> start_upload_command = {0xec, 0x73};
    std::vector<unsigned char> reported_size_command = {0xec, 0x7f, 0x0, 0x0, 0x10};
    std::vector<unsigned char> end_upload_command = {0xec, 0x73};
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Transaction Command
            .WillOnce(testing::Return(default_array)) // Start Transaction Command
            .WillOnce(testing::Return(default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(default_array)) // Start Upload Command
            .WillOnce(testing::Return(default_array)) // Reported Size Command
            .WillOnce(testing::Return(default_array)); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([transaction_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([start_transaction_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([select_memory_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([start_upload_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([reported_size_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([end_upload_command](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteFail) {
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock =
            std::make_shared<testing::NiceMock<FileHandleMock>>();
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    std::shared_ptr<testing::NiceMock<TransformToolMock>> transform_tool_mock =
            std::make_shared<testing::NiceMock<TransformToolMock>>();
    file_handle_mock->SetIterations(1);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[65]));
    file_handle_mock->SetSize(65);
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    std::vector<unsigned char> default_array(65, 0);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)); // Default Gif
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true)); // Default Gif
    EXPECT_EQ(upload_chain.Execute(), false);
}
