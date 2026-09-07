#include "commands/command_chain.h"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mocks/base_command_mock.h"

class CommandChainTest : public testing::Test {};

TEST_F(CommandChainTest, AddCommandSuccess) {
    CommandChain command_chain{};
    BaseCommandMock *mock1 = new BaseCommandMock(nullptr);
    BaseCommandMock *mock2 = new BaseCommandMock(nullptr);
    command_chain.AddCommand(mock1);
    command_chain.AddCommand(mock2);
    EXPECT_EQ(command_chain.current_command, mock1);
    EXPECT_EQ(command_chain.next_command_chain->current_command, mock2);
}

TEST_F(CommandChainTest, ExecuteSuccess) {
    CommandChain command_chain{};
    BaseCommandMock *mock1 = new BaseCommandMock(nullptr);
    EXPECT_CALL(*mock1, Execute()).Times(1);
    ON_CALL(*mock1, Execute).WillByDefault(testing::Return(true));
    command_chain.AddCommand(mock1);
    EXPECT_EQ(command_chain.current_command, mock1);
    EXPECT_EQ(command_chain.Execute(), true);
}

TEST_F(CommandChainTest, ExecuteFail) {
    CommandChain command_chain{};
    BaseCommandMock *mock1 = new BaseCommandMock(nullptr);
    EXPECT_CALL(*mock1, Execute()).Times(1);
    ON_CALL(*mock1, Execute).WillByDefault(testing::Return(false));
    command_chain.AddCommand(mock1);
    EXPECT_EQ(command_chain.current_command, mock1);
    EXPECT_EQ(command_chain.Execute(), false);
}

TEST_F(CommandChainTest, ExecuteMultipleCommands) {
    CommandChain command_chain{};
    BaseCommandMock *mock1 = new BaseCommandMock(nullptr);
    BaseCommandMock *mock2 = new BaseCommandMock(nullptr);
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
