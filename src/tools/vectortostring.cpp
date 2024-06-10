// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#include <tools/vectortostring.h>

namespace TOOLS {
    std::string VectorToString(std::vector<tOTP_object> tOTPObjects) {
        std::string ret = "";
        unsigned long long int j = tOTPObjects.size() - 1;
        for (unsigned long long int i = 0; i < j; ++i) {
            ret += tOTPObjects[i].tag + '\r' + tOTPObjects[i].secret + '\r' + std::to_string(tOTPObjects[i].period) + '\r' + tOTPObjects[i].alg + '\r' + std::to_string(tOTPObjects[i].digits) + '\n';
        }
        ret += tOTPObjects[j].tag + '\r' + tOTPObjects[j].secret + '\r' + std::to_string(tOTPObjects[j].period) + '\r' + tOTPObjects[j].alg + '\r' + std::to_string(tOTPObjects[j].digits);
        return ret;
    }
}