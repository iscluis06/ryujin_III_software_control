#ifndef RYUJINIII_FACTORY_H
#define RYUJINIII_FACTORY_H

#include <string>
#include "base_factory.h"
#include "libusb_wrapper.h"

class Factory : public BaseFactory {
public:
    Factory(std::shared_ptr<LibUsbWrapperBase> wrapper);
    std::unique_ptr<BaseCommand> GetCommand(std::string command) override;
    std::unique_ptr<BaseCommand> GetCommand(std::string command, int index) override;
    std::unique_ptr<CommandChain> GetChain(std::string command, int index) override;
    std::unique_ptr<CommandChain> GetChain(std::string command, std::string path, int index) override;

private:
    std::shared_ptr<LibUsbWrapperBase> wrapper_;
};

#endif // RYUJINIII_FACTORY_H
