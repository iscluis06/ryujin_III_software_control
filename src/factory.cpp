#include "factory.h"

#include "commands/delete_chain.h"
#include "commands/select_gif_command.h"
#include "commands/turn_off_command.h"
#include "commands/turn_on_command.h"
#include "commands/upload_chain.h"
#include "file_handle.h"
#include "magick_tool.h"

Factory::Factory(std::shared_ptr<LibUsbWrapperBase> wrapper) : wrapper_(std::move(wrapper)) {}
std::unique_ptr<BaseCommand> Factory::GetCommand(std::string command) {
    if (command == "turn_on") {
        return std::make_unique<TurnOnCommand>(wrapper_);
    }
    if (command == "turn_off") {
        return std::make_unique<TurnOffCommand>(wrapper_);
    }
    return nullptr;
}
std::unique_ptr<BaseCommand> Factory::GetCommand(std::string command, int index) {
    if (command == "select_gif_from_memory") {
        return std::make_unique<SelectGifCommand>(wrapper_, index);
    }
    return nullptr;
}
std::unique_ptr<CommandChain> Factory::GetChain(std::string command, int index) {
    if (command == "delete_from_memory") {
        return std::make_unique<DeleteChain>(wrapper_, index);
    }
    return nullptr;
}

std::unique_ptr<CommandChain> Factory::GetChain(std::string command, std::string path, int index) {
    if (command == "upload_gif") {
        std::shared_ptr<FileHandleBase> file_handle = std::make_shared<FileHandle>();
        std::shared_ptr<TransformToolBase> transform_tool = std::make_shared<MagickTool>();
        return std::make_unique<UploadChain>(transform_tool, file_handle, wrapper_, path, index);
    }
    return nullptr;
}
