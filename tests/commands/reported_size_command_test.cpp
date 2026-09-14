#include "commands/reported_size_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class ReportedSizeCommandTest : public testing::Test {
protected:
    void SetUp() { this->mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>(); }
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    std::vector<unsigned char> default_array = std::vector<unsigned char>(65, 0);
    std::vector<unsigned char> size = {0x00, 0xff, 0x1f};
    std::vector<unsigned char> valid_response = {0xec, 0x7f, 0x0, 0x0, 0x10};
};

TEST_F(ReportedSizeCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    ReportedSizeCommand reported_size_command(this->mock, this->size);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(reported_size_command.Execute(), true);
}

TEST_F(ReportedSizeCommandTest, ExecuteFail) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    ReportedSizeCommand reported_size_command(this->mock, this->size);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(reported_size_command.Execute(), false);
}

TEST_F(ReportedSizeCommandTest, InvalidResponse) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    ReportedSizeCommand reported_size_command(this->mock, this->size);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(reported_size_command.Execute(), false);
}
