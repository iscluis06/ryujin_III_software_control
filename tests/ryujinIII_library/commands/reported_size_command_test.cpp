#include "commands/reported_size_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class ReportedSizeCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
        size = {0x00, 0xff, 0x1f};
        valid_response = {0xec, 0x7f, 0x0, 0x0, 0x10};
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
    static std::vector<unsigned char> size;
    static std::vector<unsigned char> valid_response;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> ReportedSizeCommandTest::mock;
std::vector<unsigned char> ReportedSizeCommandTest::default_array;
std::vector<unsigned char> ReportedSizeCommandTest::size;
std::vector<unsigned char> ReportedSizeCommandTest::valid_response;

TEST_F(ReportedSizeCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    ReportedSizeCommand reported_size_command(mock, size);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = valid_response;
                return true;
            });
    EXPECT_EQ(reported_size_command.Execute(), true);
}

TEST_F(ReportedSizeCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    ReportedSizeCommand reported_size_command(mock, size);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(reported_size_command.Execute(), false);
}

TEST_F(ReportedSizeCommandTest, InvalidResponse) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    ReportedSizeCommand reported_size_command(mock, size);
    EXPECT_CALL(*(mock.get()), SendInterrupt)
            .WillOnce(testing::Return(true))
            .WillOnce([](unsigned char endpoint, std::vector<unsigned char> &data) {
                data = default_array;
                return true;
            });
    EXPECT_EQ(reported_size_command.Execute(), false);
}
