#include "states/upload_chain.h"
#include "states/transaction_state.h"
#include "states/start_transaction_state.h"
#include "states/select_memory_space_state.h"
#include "states/start_upload_state.h"
#include "states/reported_size_state.h"
#include "states/upload_gif_state.h"
#include "states/end_upload_state.h"

UploadChain::UploadChain(std::shared_ptr<libusb_device_handle *> device, const std::string &path,
                         int memory_index) : StateChain(UploadChain::retry_,
                                                        UploadChain::kMaxTries_),
                                             file_handle(FileHandle(path)) {
    std::list<std::shared_ptr<BaseState> > states;
    states.emplace_back(std::make_shared<TransactionState>(device));
    states.emplace_back(std::make_shared<StartTransactionState>(device));
    states.emplace_back(std::make_shared<SelectMemorySpaceState>(device, memory_index));
    states.emplace_back(std::make_shared<StartUploadState>(device));
    states.emplace_back(std::make_shared<ReportedSizeState>(device, file_handle.GetSizeToHex()));
    states.emplace_back(std::make_shared<UploadGifState>(device, file_handle));
    states.emplace_back(std::make_shared<EndUploadState>(device));
    this->SetStateList(states);
}
