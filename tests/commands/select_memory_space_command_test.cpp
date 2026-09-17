#include "commands/select_memory_space_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class SelectMemorySpaceCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
        valid_response = {0xec, 0x72};
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
    static std::vector<unsigned char> valid_response;
    static constexpr int kMemoryIndex = 1;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SelectMemorySpaceCommandTest::mock;
std::vector<unsigned char> SelectMemorySpaceCommandTest::default_array;
std::vector<unsigned char> SelectMemorySpaceCommandTest::valid_response;

TEST_F(SelectMemorySpaceCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SelectMemorySpaceCommand select_memory_space_command(mock, kMemoryIndex);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(select_memory_space_command.Execute(), true);
}

TEST_F(SelectMemorySpaceCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SelectMemorySpaceCommand select_memory_space_command(mock, kMemoryIndex);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(select_memory_space_command.Execute(), false);
}

TEST_F(SelectMemorySpaceCommandTest, InvalidResponse) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    SelectMemorySpaceCommand select_memory_space_command(mock, kMemoryIndex);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(select_memory_space_command.Execute(), false);
}
