#include "commands/upload_chain.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "file_handle_mock.h"
#include "libusb_wrapper_mock.h"
#include "transform_tool_mock.h"

class UploadChainTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        file_handle_mock = std::make_shared<testing::NiceMock<FileHandleMock>>();
        wrapper_mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        transform_tool_mock = std::make_shared<testing::NiceMock<TransformToolMock>>();
        default_array = std::vector<unsigned char>(65, 0);
        transaction_command = {0xec, 0x71};
        start_transaction_command = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
        select_memory_command = {0xec, 0x72};
        start_upload_command = {0xec, 0x73};
        reported_size_command = {0xec, 0x7f, 0x0, 0x0, 0x10};
        end_upload_command = {0xec, 0x73};
    }
    static void TearDownTestSuite() {
        file_handle_mock.reset();
        wrapper_mock.reset();
        transform_tool_mock.reset();
    }
    static std::shared_ptr<testing::NiceMock<FileHandleMock>> file_handle_mock;
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> wrapper_mock;
    static std::shared_ptr<testing::NiceMock<TransformToolMock>> transform_tool_mock;
    static std::vector<unsigned char> default_array;
    static std::vector<unsigned char> transaction_command;
    static std::vector<unsigned char> start_transaction_command;
    static std::vector<unsigned char> select_memory_command;
    static std::vector<unsigned char> start_upload_command;
    static std::vector<unsigned char> reported_size_command;
    static std::vector<unsigned char> end_upload_command;
    static constexpr int kDefaultIterations = 1;
    static constexpr int kDefaultBufferSize = 65;
};

std::shared_ptr<testing::NiceMock<FileHandleMock>> UploadChainTest::file_handle_mock;
std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> UploadChainTest::wrapper_mock;
std::shared_ptr<testing::NiceMock<TransformToolMock>> UploadChainTest::transform_tool_mock;
std::vector<unsigned char> UploadChainTest::default_array;
std::vector<unsigned char> UploadChainTest::transaction_command;
std::vector<unsigned char> UploadChainTest::start_transaction_command;
std::vector<unsigned char> UploadChainTest::select_memory_command;
std::vector<unsigned char> UploadChainTest::start_upload_command;
std::vector<unsigned char> UploadChainTest::reported_size_command;
std::vector<unsigned char> UploadChainTest::end_upload_command;

TEST_F(UploadChainTest, ExecuteSuccessFirstTry) {
    file_handle_mock->SetIterations(kDefaultIterations);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[kDefaultBufferSize]));
    file_handle_mock->SetSize(kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Transaction Command
            .WillOnce(testing::Return(default_array)) // Start Transaction Command
            .WillOnce(testing::Return(default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(default_array)) // Start Upload Command
            .WillOnce(testing::Return(default_array)) // Reported Size Command
            .WillOnce(testing::Return(default_array)); // End Upload Command
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteSuccessSecondTry) {
    file_handle_mock->SetIterations(kDefaultIterations);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[kDefaultBufferSize]));
    file_handle_mock->SetSize(kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Transaction Command
            .WillOnce(testing::Return(default_array)) // Start Transaction Command
            .WillOnce(testing::Return(default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(default_array)) // Start Upload Command
            .WillOnce(testing::Return(default_array)) // Reported Size Command
            .WillOnce(testing::Return(default_array)); // End Upload Command
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteSuccessThirdTry) {
    file_handle_mock->SetIterations(kDefaultIterations);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[kDefaultBufferSize]));
    file_handle_mock->SetSize(kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Transaction Command
            .WillOnce(testing::Return(default_array)) // Start Transaction Command
            .WillOnce(testing::Return(default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(default_array)) // Start Upload Command
            .WillOnce(testing::Return(default_array)) // Reported Size Command
            .WillOnce(testing::Return(default_array)); // End Upload Command
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true)) // Default Gif
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = transaction_command;
                return true;
            }) // Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_transaction_command;
                return true;
            }) // Start Transaction Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = select_memory_command;
                return true;
            }) // Select Memory Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = start_upload_command;
                return true;
            }) // Start Upload Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = reported_size_command;
                return true;
            }) // Reported Size Command
            .WillOnce(testing::Return(true)) // Upload Gif Command
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = end_upload_command;
                return true;
            }); // End Upload Command
    EXPECT_CALL(*(wrapper_mock.get()), SendBulk).WillRepeatedly(testing::Return(true));


    EXPECT_EQ(upload_chain.Execute(), true);
}

TEST_F(UploadChainTest, ExecuteFail) {
    file_handle_mock->SetIterations(kDefaultIterations);
    file_handle_mock->SetBuffer(std::shared_ptr<unsigned char[]>(new unsigned char[kDefaultBufferSize]));
    file_handle_mock->SetSize(kDefaultBufferSize);
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(wrapper_mock.get()), FillArray)
            .WillOnce(testing::Return(default_array)) // Default Gif
            .WillOnce(testing::Return(default_array)) // Transaction Command
            .WillOnce(testing::Return(default_array)) // Start Transaction Command
            .WillOnce(testing::Return(default_array)) // Select Memory Space Command
            .WillOnce(testing::Return(default_array)) // Start Upload Command
            .WillOnce(testing::Return(default_array)) // Reported Size Command
            .WillOnce(testing::Return(default_array)); // End Upload Command
    EXPECT_CALL(*(transform_tool_mock.get()), IsAvailable).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), ReadFile).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*(file_handle_mock.get()), GetIterations).WillRepeatedly(testing::Return(1));
    UploadChain upload_chain{transform_tool_mock, file_handle_mock, wrapper_mock, "", 1};
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(false)); // Default Gif
    EXPECT_EQ(upload_chain.Execute(), false);
}
