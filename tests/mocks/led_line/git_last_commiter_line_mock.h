#ifndef RYUJINIII_GIT_LAST_COMMITER_LINE_MOCK_H
#define RYUJINIII_GIT_LAST_COMMITER_LINE_MOCK_H

#include <gmock/gmock.h>
#include "led_line/git_last_commiter_line.h"

class GitLastCommiterLineMock : public GitLastCommiterLine {
public:
    GitLastCommiterLineMock(const std::string &git_path) : GitLastCommiterLine(git_path) {};
    MOCK_METHOD(std::string, ExecuteCommiterName, (), (override));
    MOCK_METHOD(std::string, ExecuteCommitDate, (), (override));
};

#endif // RYUJINIII_GIT_LAST_COMMITER_LINE_MOCK_H
