#include "commands/upload_chain.h"

#include "commands/default_gif_command.h"
#include "commands/end_upload_command.h"
#include "commands/reported_size_command.h"
#include "commands/select_memory_space_command.h"
#include "commands/start_transaction_command.h"
#include "commands/start_upload_command.h"
#include "commands/transaction_command.h"
#include "commands/upload_gif_command.h"
#include "magick_tool.h"
#include "ryujin_device.h"

#include <iostream>

#include "date_utils.h"
#include "stores/memory_slots_store.h"

UploadChain::UploadChain(std::shared_ptr<TransformToolBase> transform_tool, std::shared_ptr<FileHandleBase> file_tool,
                         std::shared_ptr<LibUsbWrapperBase> wrapper, const std::string &path, int memory_index) :
    CommandChain() {
    index_ = memory_index;
    if (!transform_tool->IsAvailable()) {
        std::cout << "DISABLED" << std::endl;
        return;
    }
    std::string gif_name = DateUtils::GetFullTimeStamp() + ".gif";
    std::string final_path = std::string(RyujinConstants::kRyujinPersistentDirectory) + "/" + gif_name;
    transform_tool->Transform(path, final_path);
    file_tool_ = file_tool;
    file_tool_->SetPath(final_path);
    if (!file_tool_->Initialize()) {
        std::cerr << "File not found " << std::endl;
        return;
    }
    this->AddCommand(new DefaultGifCommand(wrapper));
    this->AddCommand(new TransactionCommand(wrapper));
    this->AddCommand(new StartTransactionCommand(wrapper));
    this->AddCommand(new SelectMemorySpaceCommand(wrapper, memory_index));
    this->AddCommand(new StartUploadCommand(wrapper));
    this->AddCommand(new ReportedSizeCommand(wrapper, file_tool->GetSizeToHex()));
    this->AddCommand(new UploadGifCommand(wrapper, file_tool));
    this->AddCommand(new EndUploadCommand(wrapper));
}

bool UploadChain::Execute() {
    int no_retries = 0;
    bool result = false;
    while (no_retries < this->kMaxTries_) {
        if (this->CommandChain::Execute()) {
            result = true;
            break;
        }
        no_retries++;
    }
    MemorySlotsStore slots(RyujinConstants::kRyujinPersistentDirectory);
    slots.WriteSlot(index_, file_tool_->GetPath());
    slots.UpdateSlots();
    return result;
}
