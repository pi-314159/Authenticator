// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#include <tools/generateiv.h>

#include <random>

namespace TOOLS {
    void GenerateIV(unsigned char* iV, unsigned int iVSize) {
        std::mt19937 devRandom(std::random_device{}());
        std::uniform_int_distribution<>IVrange{0, 255};
        for (unsigned short int i = 0; i < iVSize; ++i) {
            iV[i] = IVrange(devRandom);
        }
        return;
    }
}