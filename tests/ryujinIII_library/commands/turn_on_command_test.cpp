#include "commands/turn_on_command.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"

class TurnOnCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> TurnOnCommandTest::mock;
std::vector<unsigned char> TurnOnCommandTest::default_array;

TEST_F(TurnOnCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    TurnOnCommand turn_on_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));
    EXPECT_EQ(turn_on_command.Execute(), true);
}

TEST_F(TurnOnCommandTest, ExecuteFail) {
    EXPECT_CALL(*(mock.get()), FillArray).WillOnce(testing::Return(default_array));
    TurnOnCommand turn_on_command(mock);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(turn_on_command.Execute(), false);
}
