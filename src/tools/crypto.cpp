// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#include <tools/crypto.h>

#include <openssl/evp.h>
#include <openssl/hmac.h>

#include <ranges>

namespace TOOLS {
    void Crypto::CalculateHmac(char hashAlg, unsigned char* key, int& keySize, unsigned long long int msg, unsigned char* result, unsigned int* resultSize) {
        auto hashAlgorithm = EVP_sha1();
        switch (hashAlg) {
        case '2':
            hashAlgorithm = EVP_sha256();
            break;
        case '3':
            hashAlgorithm = EVP_sha384();
            break;
        case '5':
            hashAlgorithm = EVP_sha512();
            break;
        }

        unsigned char message[8] = {'0'};
        // This automatically solves the endianness problem
        for (const short int i : std::views::iota(0, 8)) {
            message[i] = (char)(unsigned char)(msg >> (56 - 8 * i));
        }

        HMAC(hashAlgorithm, key, keySize, message, 8, result, resultSize);
        return;
    }

    void Crypto::Aes(unsigned char* key, unsigned char* iV, std::string& input, std::string& output, unsigned long long int& outputSize, bool encrypt, unsigned short int bufferSize) {
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        EVP_CipherInit_ex(ctx, EVP_aes_256_ctr(), NULL, key, iV, encrypt);
        unsigned char* inputBuffer = new unsigned char[bufferSize];
        unsigned char* outputBuffer = new unsigned char[bufferSize + 16];
        int outputBufferSize;
        unsigned long long int inputSize = input.length();
        output = "";
        outputSize = 0;
        std::string temp;

        for (unsigned long long int i = 0; i + bufferSize <= inputSize; i += bufferSize) {
            temp = input.substr(i, bufferSize);
            temp.copy(reinterpret_cast<char*>(inputBuffer), temp.length());
            EVP_CipherUpdate(ctx, outputBuffer, &outputBufferSize, inputBuffer, bufferSize);
            output += std::string(reinterpret_cast<char*>(outputBuffer), outputBufferSize);
            outputSize += outputBufferSize;
        }

        temp = input.substr(inputSize - (inputSize % bufferSize));
        temp.copy(reinterpret_cast<char*>(inputBuffer), temp.length());
        EVP_CipherUpdate(ctx, outputBuffer, &outputBufferSize, inputBuffer, inputSize % bufferSize);
        output += std::string(reinterpret_cast<char*>(outputBuffer), outputBufferSize);
        outputSize += outputBufferSize;
        EVP_CipherFinal(ctx, outputBuffer, &outputBufferSize);
        output += std::string(reinterpret_cast<char*>(outputBuffer), outputBufferSize);
        outputSize += outputBufferSize;

        EVP_CIPHER_CTX_free(ctx);
        delete[] inputBuffer; delete[] outputBuffer;
        return;
    }
}