#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../mocks/commands/base_command_mock.h"

class BaseCommandTest : public testing::Test {};

TEST_F(BaseCommandTest, IsMessageValidSuccess) {
    std::vector<unsigned char> message = {74, 65, 73, 74};
    BaseCommandMock base_command(message.data(), message.size());
    EXPECT_EQ(base_command.IsMessageValid(message), true);
}

TEST_F(BaseCommandTest, IsMessageValidFail) {
    std::vector<unsigned char> message = {74, 65, 73, 74};
    std::vector<unsigned char> second_message = {74, 65, 73, 73};
    BaseCommandMock base_command(message.data(), message.size());
    EXPECT_EQ(base_command.IsMessageValid(second_message), false);
}
