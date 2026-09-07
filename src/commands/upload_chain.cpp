#include "commands/upload_chain.h"

#include "commands/default_gif.h"
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

const std::string UploadChain::kFinalGifPath_ = "/tmp/ryujin.gif";

UploadChain::UploadChain(std::shared_ptr<TransformToolBase> transform_tool, std::shared_ptr<FileHandleBase> file_tool,
                         std::shared_ptr<LibUsbWrapperBase> wrapper, const std::string &path, int memory_index) :
    CommandChain() {
    if (!transform_tool->IsAvailable()) {
        std::cout << "DISABLED" << std::endl;
        return;
    }
    transform_tool->Transform(path, this->kFinalGifPath_);
    file_tool->SetPath(this->kFinalGifPath_);
    if (!file_tool->Initialize()) {
        std::cerr << "File not found " << std::endl;
        return;
    }
    this->AddCommand(new DefaultGif(wrapper));
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
    while (no_retries < this->kMaxTries_) {
        if (this->CommandChain::Execute()) {
            return true;
        }
        no_retries++;
    }
    return false;
}
