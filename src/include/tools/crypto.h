// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#ifndef TOOLS__CRYPTO_H_
#define TOOLS__CRYPTO_H_

#include <string>

namespace TOOLS {
    class Crypto {
    public:
        void CalculateHmac(char hashAlg, unsigned char* key, int& keySize, unsigned long long int msg, unsigned char* result, unsigned int* resultSize);
        void Aes(unsigned char* key, unsigned char* iv, std::string& input, std::string& output, unsigned long long int& outputSize, bool encrypt = true, unsigned short int bufferSize = 1024);
    };
}

#endif
