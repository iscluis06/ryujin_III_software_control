#include "commands/start_transaction_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class StartTransactionCommandTest : public testing::Test {
protected:
    void SetUp() { mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>(); }
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    std::vector<unsigned char> default_array = std::vector<unsigned char>(65, 0);
    std::vector<unsigned char> valid_response = {0xec, 0x71, 0x0, 0x1, 0xa8, 0x7e, 0x0, 0x0};
};

TEST_F(StartTransactionCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    StartTransactionCommand start_transaction_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(start_transaction_command.Execute(), true);
}

TEST_F(StartTransactionCommandTest, ExecuteFail) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(default_array));
    StartTransactionCommand start_transaction_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(start_transaction_command.Execute(), false);
}

TEST_F(StartTransactionCommandTest, InvalidResponse) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(default_array));
    StartTransactionCommand start_transaction_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(start_transaction_command.Execute(), false);
}
