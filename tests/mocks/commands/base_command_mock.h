#ifndef RYUJINIII_BASE_COMMAND_MOCK_H
#define RYUJINIII_BASE_COMMAND_MOCK_H

#include <gmock/gmock.h>
#include "commands/base_command.h"

class BaseCommandMock : public BaseCommand {
public:
    BaseCommandMock(std::shared_ptr<LibUsbWrapperBase> wrapper) : BaseCommand(std::move(wrapper)) {}
    BaseCommandMock(const unsigned char *valid_message_back, int valid_message_back_size) :
        BaseCommand(nullptr, valid_message_back, valid_message_back_size) {};
    MOCK_METHOD(bool, Execute, (), (override));
};

#endif // RYUJINIII_BASE_COMMAND_MOCK_H
