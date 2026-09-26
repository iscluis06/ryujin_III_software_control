#include "factory.h"

#include <map>
#include "commands/clock_chain.h"
#include "commands/clock_mode_command.h"
#include "commands/default_gif_command.h"
#include "commands/delete_chain.h"
#include "commands/hardware_monitor_chain.h"
#include "commands/hardware_monitor_chain_config.h"
#include "commands/select_gif_command.h"
#include "commands/select_jpeg_chain.h"
#include "commands/speed_config_command.h"
#include "commands/turn_off_command.h"
#include "commands/turn_on_command.h"
#include "commands/upload_chain.h"
#include "commands/upload_chain_jpeg.h"
#include "file_handle.h"
#include "magick_tool.h"
#include "magick_tool_jpeg.h"

Factory::Factory(std::shared_ptr<LibUsbWrapperBase> wrapper) : wrapper_(std::move(wrapper)) {}
std::unique_ptr<ExecuteBase> Factory::GetCommand(args::ArgumentParser &parser) {
    std::map<std::string, args::FlagBase *> mapped_flags;
    for (auto command: parser.GetAllFlags()) {
        if (command->Matched()) {
            mapped_flags[command->Name()] = command;
        }
    }

    if (mapped_flags.count("turn on")) {
        return std::make_unique<TurnOnCommand>(wrapper_);
    }
    if (mapped_flags.count("turn off")) {
        return std::make_unique<TurnOffCommand>(wrapper_);
    }
    if (mapped_flags.count("default gif")) {
        return std::make_unique<DefaultGifCommand>(wrapper_);
    }
    if (mapped_flags.count("hardware monitor")) {
        return std::make_unique<HardwareMonitorChain>(wrapper_);
    }
    if (mapped_flags.count("fan speed config")) {
        auto value = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["fan speed config"]);
        return std::make_unique<SpeedConfigCommand>(wrapper_, SpeedConfigCommand::DeviceSelector::FAN_DEVICE,
                                                    args::get(*value));
    }
    if (mapped_flags.count("pump speed config")) {
        auto value = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["pump speed config"]);
        return std::make_unique<SpeedConfigCommand>(wrapper_, SpeedConfigCommand::DeviceSelector::PUMP_DEVICE,
                                                    args::get(*value));
    }
    if (mapped_flags.count("select gif") && !mapped_flags.count("upload gif")) {
        auto index = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["select gif"]);
        return std::make_unique<SelectGifCommand>(wrapper_, args::get(*index));
    }
    if (mapped_flags.count("select jpeg") && !mapped_flags.count("upload jpeg")) {
        auto index = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["select jpeg"]);
        return std::make_unique<SelectJpegChain>(wrapper_, args::get(*index));
    }
    if (mapped_flags.count("delete from memory")) {
        auto index = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["delete from memory"]);
        return std::make_unique<DeleteChain>(wrapper_, args::get(*index));
    }
    if (mapped_flags.count("upload gif") && mapped_flags.count("select gif")) {
        auto path = dynamic_cast<args::ValueFlag<std::string> *>(mapped_flags["upload gif"]);
        auto index = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["select gif"]);
        std::shared_ptr<FileHandleBase> file_handle = std::make_shared<FileHandle>();
        std::shared_ptr<TransformToolBase> transform_tool = std::make_shared<MagickTool>();
        return std::make_unique<UploadChain>(transform_tool, file_handle, wrapper_, args::get(*path),
                                             args::get(*index));
    }
    if (mapped_flags.count("upload jpeg") && mapped_flags.count("select jpeg")) {
        auto path = dynamic_cast<args::ValueFlag<std::string> *>(mapped_flags["upload jpeg"]);
        auto index = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["select jpeg"]);
        std::shared_ptr<FileHandleBase> file_handle = std::make_shared<FileHandle>();
        std::shared_ptr<TransformToolBase> transform_tool = std::make_shared<MagickToolJpeg>();
        return std::make_unique<UploadChainJpeg>(transform_tool, file_handle, wrapper_, args::get(*path),
                                                 args::get(*index));
    }
    if (mapped_flags.count("clock mode")) {
        return std::make_unique<ClockChain>(wrapper_);
    }
    if (mapped_flags.count("hardware monitor config")) {
        if (!mapped_flags.count("line1") || !mapped_flags.count("mode") || !mapped_flags.count("style")) {
            std::cerr << "You must set at least line1, mode and style alongside hardware monitor config" << std::endl;
            return nullptr;
        }
        auto config = HardwareMonitorChainConfig(this->wrapper_);
        auto line1 = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["line1"]);
        auto mode = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["mode"]);
        auto style = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["style"]);
        config.AddLine(args::get(*line1));
        config.SetMode(args::get(*mode));
        config.SetStyle(args::get(*style));
        if (mapped_flags.count("line2")) {
            auto line = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["line2"]);
            config.AddLine(args::get(*line));
        }
        if (mapped_flags.count("line3")) {
            auto line = dynamic_cast<args::ValueFlag<int> *>(mapped_flags["line3"]);
            config.AddLine(args::get(*line));
        }
        if (mapped_flags.count("git repo path")) {
            auto path = dynamic_cast<args::ValueFlag<std::string> *>(mapped_flags["git repo path"]);
            config.SetGitPath(args::get(*path));
        }
        return config.GetChain();
    }
    return nullptr;
}
