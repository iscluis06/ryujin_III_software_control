#include "commands/upload_chain.h"

#include "commands/default_gif.h"
#include "commands/end_upload_command.h"
#include "commands/reported_size_command.h"
#include "commands/select_memory_space_command.h"
#include "commands/start_transaction_command.h"
#include "commands/start_upload_command.h"
#include "commands/transaction_command.h"
#include "commands/upload_gif_command.h"
#include "magick_validation.h"
#include "ryujin_device.h"

#include <iostream>

const std::string UploadChain::kFinalGifPath_ = "/tmp/ryujin.gif";

UploadChain::UploadChain(std::shared_ptr<libusb_device_handle *> device,
                         const std::string &path, int memory_index)
    : CommandChain() {
  std::string magick_transform(
      "magick " + path +
      " -coalesce -dispose 1 -resize 320x240! -background black -dither "
      "FloydSteinberg -remap netscape: -colors 64 " +
      UploadChain::kFinalGifPath_ + " && truncate -s %4096 " +
      UploadChain::kFinalGifPath_);
  if (!MagickValidation::IsAvailable()) {
    std::cout << "DISABLED" << std::endl;
    return;
  }
  std::system(magick_transform.c_str());
  this->file_handle_ = FileHandle(UploadChain::kFinalGifPath_);
  this->AddCommand(new DefaultGif(device));
  this->AddCommand(new TransactionCommand(device));
  this->AddCommand(new StartTransactionCommand(device));
  this->AddCommand(new SelectMemorySpaceCommand(device, memory_index));
  this->AddCommand(new StartUploadCommand(device));
  this->AddCommand(
      new ReportedSizeCommand(device, this->file_handle_.GetSizeToHex()));
  this->AddCommand(new UploadGifCommand(device, this->file_handle_));
  this->AddCommand(new EndUploadCommand(device));
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
