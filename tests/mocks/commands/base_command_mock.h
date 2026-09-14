#ifndef RYUJINIII_BASE_COMMAND_MOCK_H
#define RYUJINIII_BASE_COMMAND_MOCK_H

#include <gmock/gmock.h>
#include "commands/base_command.h"

class BaseCommandMock : public BaseCommand {
public:
    BaseCommandMock(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {}
    MOCK_METHOD(bool, Execute, (), (override));
    MOCK_METHOD(std::string, GetClassName, (), (const, override));
};

#endif // RYUJINIII_BASE_COMMAND_MOCK_H
