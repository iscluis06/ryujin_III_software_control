#include "commands/slide_show_command.h"
SlideShowCommand::SlideShowCommand(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> gifs) :
    BaseCommand(std::move(base)) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    this->ShouldReadBack(true);
    int instruction_number = 0;
    for (int gif: gifs) {
        this->kDefaultGifCommand[this->kGifIndex] = gif;
        this->kInstruction.insert(this->kInstruction.end(), this->kDefaultGifCommand.begin(),
                                  this->kDefaultGifCommand.end());
        instruction_number++;
        if (instruction_number == 10) {
            break;
        }
    }
    this->SetInstruction(this->kInstruction);
}
std::string SlideShowCommand::GetClassName() const { return "SlideShowCommand"; }
