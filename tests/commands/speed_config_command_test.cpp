#include "commands/speed_config_command.h"


#include <gtest/gtest.h>

#include "libusb_wrapper_mock.h"

class SpeedConfigCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> SpeedConfigCommandTest::mock;
std::vector<unsigned char> SpeedConfigCommandTest::default_array;

TEST_F(SpeedConfigCommandTest, ExecutePumpSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(2).WillRepeatedly(testing::Return(default_array));
    SpeedConfigCommand speed_config_command(mock, SpeedConfigCommand::DeviceSelector::PUMP_DEVICE, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_EQ(speed_config_command.Execute(), true);
}

TEST_F(SpeedConfigCommandTest, ExecuteFanSuccess) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(2).WillRepeatedly(testing::Return(default_array));
    SpeedConfigCommand speed_config_command(mock, SpeedConfigCommand::DeviceSelector::FAN_DEVICE, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    EXPECT_EQ(speed_config_command.Execute(), true);
}

TEST_F(SpeedConfigCommandTest, ExecutePumpFail) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(2).WillRepeatedly(testing::Return(default_array));
    SpeedConfigCommand speed_config_command(mock, SpeedConfigCommand::DeviceSelector::PUMP_DEVICE, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(speed_config_command.Execute(), false);
}

TEST_F(SpeedConfigCommandTest, ExecuteFanFail) {
    EXPECT_CALL(*(mock.get()), FillArray).Times(2).WillRepeatedly(testing::Return(default_array));
    SpeedConfigCommand speed_config_command(mock, SpeedConfigCommand::DeviceSelector::FAN_DEVICE, 1);
    EXPECT_CALL(*(mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    EXPECT_EQ(speed_config_command.Execute(), false);
}
