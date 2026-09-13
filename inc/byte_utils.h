#ifndef RYUJINIII_BYTE_UTILS_H
#define RYUJINIII_BYTE_UTILS_H

#include <map>
#include <string>
#include <vector>

class ByteUtils {
public:
    ByteUtils() = default;
    virtual ~ByteUtils() = default;
    virtual std::string GetHexRepresentation(unsigned char value);
    virtual int GetDecimalValueFromHexString(std::string hex_string);
    virtual std::vector<unsigned char> ReturnASCII(std::string string_val);

private:
    const std::map<char, int> hex_dictionary = {{'0', 0},  {'1', 1},  {'2', 2},  {'3', 3}, {'4', 4},  {'5', 5},
                                                {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9}, {'a', 10}, {'b', 11},
                                                {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};
};

#endif // RYUJINIII_BYTE_UTILS_H
