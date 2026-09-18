#include "led_line/amd_core_line.h"
#include <fstream>
#include <iostream>

AmdCoreLine::AmdCoreLine() {
    this->SetHardwareMonitorName("k10temp");
    this->AddLabel("Tdie");
    this->AddLabel("Tccd1");
}

std::string AmdCoreLine::TransformValue(std::string value) {
    try {
        int core_temp = std::stoi(value);
        float real_temp = core_temp / 1000.0f;
        return std::to_string(real_temp).substr(0, 5) + "\u2103";
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return "";
    }
}
std::string AmdCoreLine::GetTitle() { return "CPU Avg"; }
std::string AmdCoreLine::GetClassName() { return "AmdCoreLine"; }
