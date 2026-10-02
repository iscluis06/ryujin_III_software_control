#ifndef RYUJINIII_SHOW_SLOTS_COMMAND_H
#define RYUJINIII_SHOW_SLOTS_COMMAND_H
#include "base_command.h"

class ShowSlotsCommand : public ExecuteBase {
public:
    ShowSlotsCommand() = default;
    bool Execute() override;
    std::string GetClassName() const override;
};

#endif // RYUJINIII_SHOW_SLOTS_COMMAND_H
