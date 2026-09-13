#ifndef RYUJINIII_GIT_LAST_COMMIT_LINE_H
#define RYUJINIII_GIT_LAST_COMMIT_LINE_H

#include <string>
#include "led_line/led_line_base.h"

class GitLastCommiterLine : public LedLineBase {
public:
    GitLastCommiterLine(std::string git_path);
    ~GitLastCommiterLine() override = default;
    std::string GetLine() override;
    std::string GetTitle() override;
    std::string ExecuteCommiterName();
    std::string ExecuteCommitDate();
    bool GitAvailable();

private:
    std::string git_path_;
    const int commiter_max_name_ = 80;
    const int commiter_max_date_ = 11;
};

#endif // RYUJINIII_GIT_LAST_COMMIT_LINE_H
