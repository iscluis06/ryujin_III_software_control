#include "commands/hardware_status_command.h"
#include <gtest/gtest.h>
#include "libusb_wrapper_mock.h"
#include "stores/hardware_status_store_mock.h"

class HardwareStatusCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        wrapper_mock = std::make_shared<LibUsbWrapperMock>();
        hardware_status_store_mock = std::make_shared<testing::NiceMock<HardwareStatusStoreMock>>();
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() {
        wrapper_mock.reset();
        hardware_status_store_mock.reset();
    }
    static std::shared_ptr<LibUsbWrapperMock> wrapper_mock;
    static std::vector<unsigned char> default_array;
    static std::shared_ptr<testing::NiceMock<HardwareStatusStoreMock>> hardware_status_store_mock;
};

std::shared_ptr<LibUsbWrapperMock> HardwareStatusCommandTest::wrapper_mock;
std::vector<unsigned char> HardwareStatusCommandTest::default_array;
std::shared_ptr<testing::NiceMock<HardwareStatusStoreMock>> HardwareStatusCommandTest::hardware_status_store_mock;

TEST_F(HardwareStatusCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillRepeatedly(testing::Return(true));
    HardwareStatusCommand hardware_status_command(wrapper_mock, hardware_status_store_mock);
    EXPECT_EQ(hardware_status_command.Execute(), true);
}

TEST_F(HardwareStatusCommandTest, ExecuteFail) {
    EXPECT_CALL(*(wrapper_mock.get()), FillArray).WillRepeatedly(testing::Return(default_array));
    EXPECT_CALL(*(wrapper_mock.get()), SendInterrupt).WillRepeatedly(testing::Return(false));
    HardwareStatusCommand hardware_status_command(wrapper_mock, hardware_status_store_mock);
    EXPECT_EQ(hardware_status_command.Execute(), false);
}
