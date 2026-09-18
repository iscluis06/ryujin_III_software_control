#ifndef RYUJINIII_GIT_LAST_COMMIT_LINE_H
#define RYUJINIII_GIT_LAST_COMMIT_LINE_H

#include <string>
#include "led_line/led_line_base.h"

/**
 * Class to show the last commiter name of a local repo.
 */
class GitLastCommiterLine : public LedLineBase {
public:
    /**
     * Constructor for git last commiter led line implement
     * @param git_path Path to the local git repo
     */
    GitLastCommiterLine(const std::string &git_path);
    /**
     * Default destructor
     */
    ~GitLastCommiterLine() override = default;
    /**
     * Returns the commiter name
     * @return The commiter name or empty on fail
     */
    std::string GetLine() override;
    /**
     * Show the date for the last commit
     * @return The date of the last commit
     */
    std::string GetTitle() override;
    /**
     * Execute git command to get last commiter name
     * @return the raw commiter name from git command
     */
    virtual std::string ExecuteCommiterName();
    /**
     * Execute git command to get last commiter date
     * @return @return the date from last commit on following format %y%m%d %H%M%S, or empty on fail
     */
    virtual std::string ExecuteCommitDate();
    /**
     * Check if git command available on system
     * @return Returns true if git available otherwise false
     */
    bool GitAvailable();

    /**
     * Utility method for testing purposes
     * @return The class name
     */
    virtual std::string GetClassName() override;

private:
    /**
     * Path to local git repo
     */
    std::string git_path_;
    /**
     * Max name for git commiter name
     */
    const int commiter_max_name_ = 80;
    /**
     * Max date for git commit
     */
    const int commiter_max_date_ = 11;
};

#endif // RYUJINIII_GIT_LAST_COMMIT_LINE_H
