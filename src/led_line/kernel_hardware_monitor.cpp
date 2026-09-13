#include "led_line/kernel_hardware_monitor.h"
#include <filesystem>
#include <fstream>

std::string KernelHardwareMonitor::GetLine() {
    if (!this->IsHardwareNameAvailable()) {
        return "";
    }
    return this->TransformValue(this->GetInputValue());
}
void KernelHardwareMonitor::AddLabel(std::string label) { this->hardware_labels_.emplace_front(label); }
void KernelHardwareMonitor::SetHardwareMonitorName(std::string name) { this->hardware_monitor_name_ = name; }
bool KernelHardwareMonitor::IsHardwareNameAvailable() { return this->GetHardwareMonitorNamePath() != ""; }
std::string KernelHardwareMonitor::GetInputValue() {
    std::string amd_hardware_monitor_path = this->GetHardwareMonitorNamePath();
    for (auto const& hw_entry: std::filesystem::directory_iterator(amd_hardware_monitor_path)) {
        std::ifstream file{hw_entry.path()};
        if (!file.is_open()) {
            continue;
        }
        std::string line;
        getline(file, line);
        file.close();
        for (std::string label_value: hardware_labels_) {
            if (line == label_value) {
                std::string file_name = hw_entry.path();
                file_name.replace(file_name.length() - this->kInputString.length(), this->kInputString.length(),
                                  this->kInputString);
                file.open(file_name);
                line.clear();
                getline(file, line);
                return line;
            }
        }
    }
    return "";
}
std::string KernelHardwareMonitor::GetHardwareMonitorNamePath() {
    std::filesystem::path root_path = this->kHardwareMonitorPath;
    if (!std::filesystem::exists(root_path)) {
        return "";
    }
    for (auto const& dir_entry: std::filesystem::directory_iterator(root_path)) {
        std::string hardware_monitor_name_path = dir_entry.path().generic_string() + "/name";
        if (!std::filesystem::exists(hardware_monitor_name_path)) {
            continue;
        }
        std::ifstream name_file(hardware_monitor_name_path);
        std::string file_contents;
        getline(name_file, file_contents);
        name_file.close();
        if (file_contents == this->hardware_monitor_name_) {
            return dir_entry.path();
        }
    }
    return "";
}
