#include "commands/upload_chain.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "file_handle_mock.h"
#include "libusb_wrapper_mock.h"
#include "transform_tool_mock.h"

class UploadChainTest : public testing::Test {
protected:
    void SetUp() {
        file_handle_mock = std::make_shared<testing::NiceMock<FileHandleMock>>();
        wrapper_mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        transform_tool_mock = std::make_shared<testing::NiceMock<TransformToolMock>>();
    }
    std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock;
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock;
    std::shared_ptr<testing::NiceMock<TransformToolMock>> transform_tool_mock;
    std::vector<unsigned char> default_array = std::vector<unsigned char>(65, 0);
    std::vector<unsigned char> transaction_command = {0xec, 0x71};
    std::vector<unsigned char> start_transaction_command = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
    std::vector<unsigned char> select_memory_command = {0xec, 0x72};
    std::vector<unsigned char> start_upload_command = {0xec, 0x73};
    std::vector<unsigned char> reported_size_command = {0xec, 0x7f, 0x0, 0x0, 0x10};
    std::vector<unsigned char> end_upload_command = {0xec, 0x73};
    const int kDefaultIterations = 1;
    const int kDefaultBufferSize = 65;
};

TEST_F(UploadChainTest, ExecuteSuccessFirstTry) {
    this->file_handle_mock->SetIterations(kDefaultIterations);
    this->file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[this->kDefaultBufferSize]));
    this->file_handle_mock->SetSize(this->kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(this->wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(this->default_array)) // Default Gif
            .WillOnce(testing::Return(this->default_array)) // Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Start Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(this->default_array)) // Start Upload Command
            .WillOnce(testing::Return(this->default_array)) // Reported Size Command
            .WillOnce(testing::Return(this->default_array)); // End Upload Command
    EXPECT_CALL(*(this->transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{this->transform_tool_mock, this->file_handle_mock, this->wrapper_mock, "", 1};
    EXPECT_CALL(*(this->wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(this->wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteSuccessSecondTry) {
    this->file_handle_mock->SetIterations(kDefaultIterations);
    this->file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[this->kDefaultBufferSize]));
    this->file_handle_mock->SetSize(this->kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(this->wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(this->default_array)) // Default Gif
            .WillOnce(testing::Return(this->default_array)) // Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Start Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(this->default_array)) // Start Upload Command
            .WillOnce(testing::Return(this->default_array)) // Reported Size Command
            .WillOnce(testing::Return(this->default_array)); // End Upload Command
    EXPECT_CALL(*(this->transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{this->transform_tool_mock, this->file_handle_mock, this->wrapper_mock, "", 1};
    EXPECT_CALL(*(this->wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(this->wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteSuccessThirdTry) {
    this->file_handle_mock->SetIterations(kDefaultIterations);
    this->file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[this->kDefaultBufferSize]));
    this->file_handle_mock->SetSize(this->kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(this->wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(this->default_array)) // Default Gif
            .WillOnce(testing::Return(this->default_array)) // Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Start Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(this->default_array)) // Start Upload Command
            .WillOnce(testing::Return(this->default_array)) // Reported Size Command
            .WillOnce(testing::Return(this->default_array)); // End Upload Command
    EXPECT_CALL(*(this->transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{this->transform_tool_mock, this->file_handle_mock, this->wrapper_mock, "", 1};
    EXPECT_CALL(*(this->wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(this->wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteFail) {
    this->file_handle_mock->SetIterations(kDefaultIterations);
    this->file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[this->kDefaultBufferSize]));
    this->file_handle_mock->SetSize(this->kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(this->wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(this->default_array)) // Default Gif
            .WillOnce(testing::Return(this->default_array)) // Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Start Transaction Command
            .WillOnce(testing::Return(this->default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(this->default_array)) // Start Upload Command
            .WillOnce(testing::Return(this->default_array)) // Reported Size Command
            .WillOnce(testing::Return(this->default_array)); // End Upload Command
    EXPECT_CALL(*(this->transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(this->file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{this->transform_tool_mock, this->file_handle_mock, this->wrapper_mock, "", 1};
    EXPECT_CALL(*(this->wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false)); // Default Gif
    EXPECT_EQ(upload_chain.Execute(), false);
}
