#include "commands/version_command.h"


#include <fstream>
#include <gtest/gtest.h>


class VersionCommandTest : public testing::Test {};


TEST_F(VersionCommandTest, ExecuteSuccess) {
    VersionCommand version_command{};
    EXPECT_EQ(version_command.Execute(), true);
}
