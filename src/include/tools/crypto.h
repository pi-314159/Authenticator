// Author:       pi-314159@GitHub
// License:      MIT

#ifndef TOOLS__CRYPTO_H_
#define TOOLS__CRYPTO_H_

#include <openssl/evp.h>

#include <map>
#include <string>

namespace TOOLS {
    class Crypto {
    public:
        const std::map<std::string, const EVP_MD*> hashAlgorithms {
            {"sha1", EVP_sha1()},
            {"sha224", EVP_sha224()},
            {"sha256", EVP_sha256()},
            {"sha384", EVP_sha384()},
            {"sha512", EVP_sha512()}};
        void CalculateHmac(std::string hashAlg, unsigned char* key, int& keySize, unsigned long long int msg, unsigned char* result, unsigned int* resultSize);
        void Aes(unsigned char* key, unsigned char* iv, std::string& input, std::string& output, unsigned long long int& outputSize, bool encrypt = true, unsigned short int bufferSize = 1024);
    };
}

#endif
