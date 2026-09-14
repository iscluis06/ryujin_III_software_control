#include "commands/hardware_monitor_chain_config.h"

HardwareMonitorChainConfig::HardwareMonitorChainConfig(std::shared_ptr<LibUsbWrapperBase> wrapper) :
    wrapper_(std::move(wrapper)) {}

void HardwareMonitorChainConfig::AddLine(int line) {
    this->lines_.push_back(static_cast<LedLineFactory::LedLineImplementations>(line));
}
void HardwareMonitorChainConfig::SetMode(int mode) { this->mode_ = static_cast<RyujinConstants::MonitorMode>(mode); }
void HardwareMonitorChainConfig::SetStyle(int style) {
    this->style_ = static_cast<RyujinConstants::MonitorStyle>(style);
}
void HardwareMonitorChainConfig::SetGitPath(const std::string &git_path) { this->git_path_ = git_path; }
std::shared_ptr<HardwareMonitorChain> HardwareMonitorChainConfig::GetChain() {
    std::shared_ptr<HardwareMonitorChain> chain;
    if (this->lines_.size() >= 3) {
        chain = std::make_shared<HardwareMonitorChain>(this->wrapper_, this->mode_, this->style_, this->lines_[0],
                                                       this->lines_[1], this->lines_[2]);
    } else if (this->lines_.size() == 2) {
        chain = std::make_shared<HardwareMonitorChain>(this->wrapper_, this->mode_, this->style_, this->lines_[0],
                                                       this->lines_[1]);
    } else if (this->lines_.size() == 1) {
        chain = std::make_shared<HardwareMonitorChain>(this->wrapper_, this->mode_, this->style_, this->lines_[0]);
    }
    if (!this->git_path_.empty()) {
        chain->GetLedLineFactory()->SetGitPath(git_path_);
    }
    return chain;
}
