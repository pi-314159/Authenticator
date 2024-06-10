// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#ifndef TOOLS__BASE32DECODE_H_
#define TOOLS__BASE32DECODE_H_

#include <map>
#include <string>

namespace TOOLS {
    const std::map<char, unsigned short int> CONST_base32DecodeTable {
        {'A', 0},  {'B', 1},  {'C', 2},  {'D', 3},  {'E', 4},  {'F', 5},  {'G', 6},  {'H', 7},
        {'I', 8},  {'J', 9},  {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15},
        {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23},
        {'Y', 24}, {'Z', 25}, {'2', 26}, {'3', 27}, {'4', 28}, {'5', 29}, {'6', 30}, {'7', 31}};
    void Base32Decode(std::string& encodedString, unsigned char* outputString);
}

#endif
