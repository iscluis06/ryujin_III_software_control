#include <cstring>
#include <iostream>


#include "led_line/git_last_committer_line.h"

GitLastCommiterLine::GitLastCommiterLine(const std::string &git_path) : LedLineBase(), git_path_(git_path) {}

std::string GitLastCommiterLine::GetLine() { return this->ExecuteCommiterName().substr(0, 8); }

std::string GitLastCommiterLine::GetTitle() { return this->ExecuteCommitDate(); }

std::string GitLastCommiterLine::ExecuteCommiterName() {
    if (!this->GitAvailable()) {
        std::cout << "Git not available" << std::endl;
        return "";
    }
    if (this->git_path_.empty()) {
        std::cout << "Path to git local repo not set " << std::endl;
        return "";
    }
    char commiter_name[this->commiter_max_name_];
    FILE *fp;
    std::string command = "git -C " + this->git_path_ + " log -1 --pretty=format:\"%an\"";
    fp = popen(command.c_str(), "r");
    fgets(commiter_name, this->commiter_max_name_, fp);
    pclose(fp);
    if (strlen(commiter_name) == 0) {
        return "";
    }
    return commiter_name;
}
std::string GitLastCommiterLine::ExecuteCommitDate() {
    if (!this->GitAvailable()) {
        std::cout << "Git not available" << std::endl;
        return "";
    }
    if (this->git_path_.empty()) {
        std::cout << "Path to git local repo not set " << std::endl;
        return "";
    }
    char commiter_date[this->commiter_max_date_];
    FILE *fp;
    std::string command =
            "git -C " + this->git_path_ + " log -1 --pretty=format:\"%ad\" --date=format:\"%y%m%d %H%M%S\"";
    fp = popen(command.c_str(), "r");
    fgets(commiter_date, this->commiter_max_name_, fp);
    pclose(fp);
    if (strlen(commiter_date) == 0) {
        return "";
    }
    return commiter_date;
}
bool GitLastCommiterLine::GitAvailable() { return std::system("git --version > /dev/null") == 0; }
