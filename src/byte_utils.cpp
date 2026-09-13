#include "byte_utils.h"

#include <cmath>
#include <iomanip>

std::string ByteUtils::GetHexRepresentation(unsigned char value) {
    std::stringstream stream;
    stream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(value);
    return stream.str();
}

int ByteUtils::GetDecimalValueFromHexString(std::string hex_string) {
    int position = hex_string.size();
    int final_value = 0;
    for (char value: hex_string) {
        position--;
        if (position < 0) {
            break;
        }
        if (!this->hex_dictionary.count(value)) {
            continue;
        }
        int power_value = position == 0 ? 1 : std::pow(16, position);
        final_value += this->hex_dictionary.at(value) * power_value;
    }
    return final_value;
}
std::vector<unsigned char> ByteUtils::ReturnASCII(std::string string_val) {
    std::vector<unsigned char> ascii_array;
    for (char c: string_val) {
        ascii_array.push_back(static_cast<unsigned char>(c));
    }
    return ascii_array;
}
