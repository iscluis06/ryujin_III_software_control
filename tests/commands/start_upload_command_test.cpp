#include "commands/start_upload_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class StartUploadCommandTest : public testing::Test {
protected:
    void SetUp() { mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>(); }
    std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    std::vector<unsigned char> default_array = std::vector<unsigned char>(65, 0);
    std::vector<unsigned char> valid_response = {0xec, 0x73};
};

TEST_F(StartUploadCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    StartUploadCommand start_upload_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(start_upload_command.Execute(), true);
}

TEST_F(StartUploadCommandTest, ExecuteFail) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    StartUploadCommand start_upload_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(start_upload_command.Execute(), false);
}

TEST_F(StartUploadCommandTest, InvalidResponse) {
    EXPECT_CALL(*(this->mock.get()), FillArray).WillOnce(testing::Return(this->default_array));
    StartUploadCommand start_upload_command(this->mock);
    EXPECT_CALL(*(this->mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([this](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(start_upload_command.Execute(), false);
}
