#include <gtest/gtest.h>

#include "led_line/git_last_commiter_line_mock.h"

class GitLastCommiterLineTest : public testing::Test {
public:
    static void SetUpTestSuite() {
        test_path = "test";
        commiter = "Luis";
        date = "01012026 060606";
    }
    static std::string test_path;
    static std::string commiter;
    static std::string date;
};

std::string GitLastCommiterLineTest::test_path;
std::string GitLastCommiterLineTest::commiter;
std::string GitLastCommiterLineTest::date;

TEST_F(GitLastCommiterLineTest, GetLineSuccess) {
    GitLastCommiterLineMock mock(test_path);
    EXPECT_CALL(mock, ExecuteCommiterName).WillRepeatedly(testing::Return(commiter));
    EXPECT_EQ(mock.GetLine(), commiter);
}

TEST_F(GitLastCommiterLineTest, GetLineFail) {
    GitLastCommiterLineMock mock(test_path);
    EXPECT_CALL(mock, ExecuteCommiterName).WillRepeatedly(testing::Return(commiter));
    EXPECT_NE(mock.GetLine(), "");
}

TEST_F(GitLastCommiterLineTest, GetTitleSuccess) {
    GitLastCommiterLineMock mock(test_path);
    EXPECT_CALL(mock, ExecuteCommitDate).WillRepeatedly(testing::Return(date));
    EXPECT_EQ(mock.GetTitle(), date);
}

TEST_F(GitLastCommiterLineTest, GetTitleFail) {
    GitLastCommiterLineMock mock(test_path);
    EXPECT_CALL(mock, ExecuteCommitDate).WillRepeatedly(testing::Return(date));
    EXPECT_NE(mock.GetTitle(), "");
}
