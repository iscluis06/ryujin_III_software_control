#ifndef RYUJINIII_BYTE_UTILS_H
#define RYUJINIII_BYTE_UTILS_H

#include <map>
#include <string>
#include <vector>

/**
 * Helper class with multiple byte utility functions
 */
class ByteUtils {
public:
    /**
     * Default constructor
     */
    ByteUtils() = default;
    /**
     * Default destructor
     */
    virtual ~ByteUtils() = default;
    /**
     * Returns a hex string representation of value parameter
     * @param value Integer hex value to return on hex string representation
     * @return a hex string representation of value
     */
    virtual std::string GetHexRepresentation(unsigned char value);
    /**
     * Returns a integer value of the hex string
     * @param hex_string A hex string representation
     * @return the integer value of the hex string
     */
    virtual int GetDecimalValueFromHexString(std::string hex_string);
    /**
     * Return a vector of ascii values from the hex string
     * @param string_val Hex string representation
     * @return A list of ascii characters of the hex value
     */
    virtual std::vector<unsigned char> ReturnASCII(std::string string_val);

private:
    /**
     * A map structure of all hex values for quick reference.
     * <br>TODO: It may not be the fastest approach need to validate.
     */
    const std::map<char, int> hex_dictionary = {{'0', 0},  {'1', 1},  {'2', 2},  {'3', 3}, {'4', 4},  {'5', 5},
                                                {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9}, {'a', 10}, {'b', 11},
                                                {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};
};

#endif // RYUJINIII_BYTE_UTILS_H
