#include "commands/delete_chain.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mocks/base_command_mock.h"
#include "mocks/libusb_wrapper_mock.h"

class DeleteChainTest : public testing::Test {};

TEST_F(DeleteChainTest, ExecuteSuccessFirstTry) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    DeleteChain delete_chain{mock, 1};
    std::vector<unsigned char> default_array{65, 0};
    std::vector<unsigned char> space_memory_array = {0xec, 0x72};
    std::vector<unsigned char> delete_memory_array = {0xec, 0x73};
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce([space_memory_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = space_memory_array;
                return true;
            })
            .WillOnce(testing::Return(true))
            .WillOnce([delete_memory_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = delete_memory_array;
                return true;
            });


    EXPECT_EQ(delete_chain.Execute(), true);
}

TEST_F(DeleteChainTest, ExecuteSuccessSecondTry) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    DeleteChain delete_chain{mock, 1};
    std::vector<unsigned char> default_array{65, 0};
    std::vector<unsigned char> space_memory_array = {0xec, 0x72};
    std::vector<unsigned char> delete_memory_array = {0xec, 0x73};
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce([space_memory_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = space_memory_array;
                return true;
            })
            .WillOnce(testing::Return(true))
            .WillOnce([delete_memory_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = delete_memory_array;
                return true;
            });


    EXPECT_EQ(delete_chain.Execute(), true);
}

TEST_F(DeleteChainTest, ExecuteSuccessThirdTry) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    DeleteChain delete_chain{mock, 1};
    std::vector<unsigned char> default_array{65, 0};
    std::vector<unsigned char> space_memory_array = {0xec, 0x72};
    std::vector<unsigned char> delete_memory_array = {0xec, 0x73};
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce([space_memory_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = space_memory_array;
                return true;
            })
            .WillOnce(testing::Return(true))
            .WillOnce([delete_memory_array](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = delete_memory_array;
                return true;
            });


    EXPECT_EQ(delete_chain.Execute(), true);
}

TEST_F(DeleteChainTest, ExecuteFail) {
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock =
            std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
    DeleteChain delete_chain{mock, 1};
    std::vector<unsigned char> default_array{65, 0};
    std::vector<unsigned char> space_memory_array = {0xec, 0x72};
    std::vector<unsigned char> delete_memory_array = {0xec, 0x73};
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true));


    EXPECT_EQ(delete_chain.Execute(), false);
}
