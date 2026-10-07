#include "commands/upload_chain_jpeg.h"

#include "commands/default_gif_command.h"
#include "commands/end_upload_command.h"
#include "commands/reported_size_command.h"
#include "commands/start_transaction_command.h"
#include "commands/start_upload_command.h"
#include "commands/transaction_command.h"
#include "commands/upload_gif_command.h"
#include "magick_tool.h"
#include "ryujin_device.h"

#include <iostream>

#include "commands/select_memory_space_jpeg_command.h"
#include "date_utils.h"
#include "stores/memory_slots_store.h"


UploadChainJpeg::UploadChainJpeg(std::shared_ptr<TransformToolBase> transform_tool,
                                 std::shared_ptr<FileHandleBase> file_tool, std::shared_ptr<LibUsbWrapperBase> wrapper,
                                 const std::string &path, int memory_index) : CommandChain() {
    if (!transform_tool->IsAvailable()) {
        std::cout << "DISABLED" << std::endl;
        return;
    }
    this->file_tool_ = file_tool;
    this->index_ = memory_index;
    std::string gif_name = DateUtils::GetFullTimeStamp() + ".jpeg";
    std::string final_path = std::string(RyujinConstants::kRyujinPersistentDirectory) + "/" + gif_name;
    transform_tool->Transform(path, final_path);
    this->file_tool_->SetPath(final_path);
    if (!file_tool->Initialize()) {
        std::cerr << "File not found " << std::endl;
        return;
    }
    this->AddCommand(new DefaultGifCommand(wrapper));
    this->AddCommand(new TransactionCommand(wrapper));
    this->AddCommand(new StartTransactionCommand(wrapper));
    this->AddCommand(new SelectMemorySpaceJPEGCommand(wrapper, memory_index));
    this->AddCommand(new StartUploadCommand(wrapper));
    this->AddCommand(new ReportedSizeCommand(wrapper, file_tool->GetSizeToHex()));
    this->AddCommand(new UploadGifCommand(wrapper, file_tool));
    this->AddCommand(new EndUploadCommand(wrapper));
}

bool UploadChainJpeg::Execute() {
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
    slots.WriteSlot(index_, file_tool_->GetPath(), MemorySlotsStore::SlotType::JPEG);
    slots.UpdateSlots();
    return result;
}
