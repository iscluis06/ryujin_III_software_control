#include "commands/command_chain.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "commands/base_command_mock.h"
#include "libusb_wrapper_mock.h"

class CommandChainTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<LibUsbWrapperMock>>();
        mock1 = new BaseCommandMock(mock);
        mock2 = new BaseCommandMock(mock);
    }
    static void TearDownTestSuite() {
        delete mock1;
        delete mock2;
    }

    void TearDown() {
        mock1 = new BaseCommandMock(mock);
        mock2 = new BaseCommandMock(mock);
    }
    static std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> mock;
    static BaseCommandMock *mock1;
    static BaseCommandMock *mock2;
};
std::shared_ptr<testing::NiceMock<LibUsbWrapperMock>> CommandChainTest::mock;
BaseCommandMock *CommandChainTest::mock1;
BaseCommandMock *CommandChainTest::mock2;

TEST_F(CommandChainTest, AddCommandSuccess) {
    CommandChain command_chain{};
    command_chain.AddCommand(mock1);
    command_chain.AddCommand(mock2);
    EXPECT_EQ(command_chain.current_command, mock1);
    EXPECT_EQ(command_chain.next_command_chain->current_command, mock2);
}

TEST_F(CommandChainTest, ExecuteSuccess) {
    CommandChain command_chain{};
    EXPECT_CALL(*mock1, Execute()).Times(1);
    ON_CALL(*mock1, Execute).WillByDefault(testing::Return(true));
    command_chain.AddCommand(mock1);
    EXPECT_EQ(command_chain.current_command, mock1);
    EXPECT_EQ(command_chain.Execute(), true);
}

TEST_F(CommandChainTest, ExecuteFail) {
    CommandChain command_chain{};
    EXPECT_CALL(*mock1, Execute()).Times(1);
    ON_CALL(*mock1, Execute).WillByDefault(testing::Return(false));
    command_chain.AddCommand(mock1);
    EXPECT_EQ(command_chain.current_command, mock1);
    EXPECT_EQ(command_chain.Execute(), false);
}

TEST_F(CommandChainTest, ExecuteMultipleCommands) {
    CommandChain command_chain{};
    EXPECT_CALL(*mock1, Execute()).Times(1);
    ON_CALL(*mock1, Execute).WillByDefault(testing::Return(true));
    EXPECT_CALL(*mock2, Execute()).Times(1);
    ON_CALL(*mock2, Execute).WillByDefault(testing::Return(true));
    command_chain.AddCommand(mock1);
    command_chain.AddCommand(mock2);
    EXPECT_EQ(command_chain.current_command, mock1);
    EXPECT_EQ(command_chain.next_command_chain->current_command, mock2);
    EXPECT_EQ(command_chain.Execute(), true);
}
