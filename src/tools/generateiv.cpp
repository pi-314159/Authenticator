// Author:       pi-314159@GitHub
// License:      MIT

#include <tools/generateiv.h>

#include <random>

namespace TOOLS {
    void GenerateIv(unsigned char* iV, unsigned int iVSize) {
        std::mt19937 devRandom(std::random_device{}());
        std::uniform_int_distribution<>iVRange{0, 255};
        for (unsigned short int i = 0; i < iVSize; ++i) {
            iV[i] = iVRange(devRandom);
        }
        return;
    }
}