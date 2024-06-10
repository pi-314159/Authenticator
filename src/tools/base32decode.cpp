// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#include <tools/base32decode.h>

namespace TOOLS {
    void Base32Decode(std::string& encodedString, unsigned char* outputString) {
        short int n = 0;
        unsigned long long int m = 0;
        unsigned short a = 0, b = 0;
        for (char& s : encodedString) {
            if (n < 3) {
                a |= (CONST_base32DecodeTable.at(s) << (3 - n));
                n += 5;
            }
            else {
                b = CONST_base32DecodeTable.at(s);
                outputString[m] = char(a | (b >> (n - 3)));
                a = (b << (11 - n));
                n -= 3;
                ++m;
            }
        }
        return;
    }
}