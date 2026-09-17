#include "commands/delete_chain.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "commands/base_command_mock.h"
#include "libusb_wrapper_mock.h"

class DeleteChainTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
        space_memory_array = {0xec, 0x72};
        delete_memory_array = {0xec, 0x73};
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
    static std::vector<unsigned char> space_memory_array;
    static std::vector<unsigned char> delete_memory_array;
    static constexpr int kMemoryIndex = 1;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> DeleteChainTest::mock;
std::vector<unsigned char> DeleteChainTest::default_array;
std::vector<unsigned char> DeleteChainTest::space_memory_array;
std::vector<unsigned char> DeleteChainTest::delete_memory_array;

TEST_F(DeleteChainTest, ExecuteSuccessFirstTry) {
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    DeleteChain delete_chain{mock, kMemoryIndex};

    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = space_memory_array;
                return true;
            })
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = delete_memory_array;
                return true;
            });


    EXPECT_EQ(delete_chain.Execute(), true);
}

TEST_F(DeleteChainTest, ExecuteSuccessSecondTry) {
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    DeleteChain delete_chain{mock, kMemoryIndex};


    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = space_memory_array;
                return true;
            })
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = delete_memory_array;
                return true;
            });


    EXPECT_EQ(delete_chain.Execute(), true);
}

TEST_F(DeleteChainTest, ExecuteSuccessThirdTry) {
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    DeleteChain delete_chain{mock, kMemoryIndex};
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = space_memory_array;
                return true;
            })
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = delete_memory_array;
                return true;
            });


    EXPECT_EQ(delete_chain.Execute(), true);
}

TEST_F(DeleteChainTest, ExecuteFail) {
    // Delete chain - Default Gif setup
    EXPECT_CALL(*(mock.get()), FillArray)
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array))
            .WillOnce(testing::Return(default_array));
    DeleteChain delete_chain{mock, kMemoryIndex};
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false))
            .WillOnce(testing::Return(true))
            .WillOnce(testing::Return(false));


    EXPECT_EQ(delete_chain.Execute(), false);
}
