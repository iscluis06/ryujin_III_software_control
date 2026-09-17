#include "commands/transaction_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class TransactionCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
        valid_response = {0xec, 0x71};
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
    static std::vector<unsigned char> valid_response;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> TransactionCommandTest::mock;
std::vector<unsigned char> TransactionCommandTest::default_array;
std::vector<unsigned char> TransactionCommandTest::valid_response;

TEST_F(TransactionCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    TransactionCommand transaction_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(transaction_command.Execute(), true);
}

TEST_F(TransactionCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    TransactionCommand transaction_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(transaction_command.Execute(), false);
}

TEST_F(TransactionCommandTest, InvalidResponse) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    TransactionCommand transaction_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(transaction_command.Execute(), false);
}
