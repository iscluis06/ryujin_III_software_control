#include "commands/slide_show_jpeg_command.h"
std::string SlideShowJpegCommand::GetClassName() const { return "SlideShowJpegCommand"; }
SlideShowJpegCommand::SlideShowJpegCommand(std::shared_ptr<LibUsbWrapperBase> base, const std::vector<int> &indexes) :
    BaseCommand(std::move(base)) {
    this->SetEndpointIn(RyujinConstants::kHidDeviceIn);
    this->SetEndpointOut(RyujinConstants::kHidDeviceOut);
    int instruction_number = 0;
    for (int index: indexes) {
        this->kDefaultJpegCommand[this->kJpegIndex] = index;
        this->kDefaultJpegCommand[this->kIncrementIndex] = instruction_number;
        this->kInstruction.insert(this->kInstruction.end(), this->kDefaultJpegCommand.begin(),
                                  this->kDefaultJpegCommand.end());
        instruction_number++;
        if (instruction_number == 10) {
            break;
        }
    }
    this->SetInstruction(this->kInstruction);
}
