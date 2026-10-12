#include "commands/version_command.h"
#include <iostream>
bool VersionCommand::Execute() {
    std::cout << "ryujinIII library version " << RYUJINIII_VERSION << std::endl;
    return true;
}
std::string VersionCommand::GetVersion() { return RYUJINIII_VERSION; }
std::string VersionCommand::GetClassName() const { return "VersionCommand"; }
