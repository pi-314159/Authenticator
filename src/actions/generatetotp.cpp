// Author:       pi-314159@GitHub
// License:      MIT

#include <actions/generatetotp.h>
#include <tools/base32decode.h>

#include <chrono>
#include <cmath>

namespace ACTIONS {
    std::string GenerateTotp(tOTP_object& tOTP, TOOLS::Crypto& crypto) {
        auto secretSize = static_cast<int>(floor(tOTP.secret.size() / 1.6));
        unsigned char* decodedSecret = new unsigned char[secretSize];
        TOOLS::Base32Decode(tOTP.secret, decodedSecret);
        unsigned char* HMACDigest = new unsigned char[64];
        unsigned int* HMACDigestSize = new unsigned int(0);
        crypto.CalculateHmac(tOTP.alg, decodedSecret, secretSize, std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() / tOTP.period, HMACDigest, HMACDigestSize);
        delete[] decodedSecret;
        short offset = HMACDigest[*HMACDigestSize - 1] & 0xf;
        unsigned int result = ((HMACDigest[offset] & 0x7f) << 24) | ((HMACDigest[offset + 1] & 0xff) << 16) | ((HMACDigest[offset + 2] & 0xff) << 8) | (HMACDigest[offset + 3] & 0xff);
        delete[] HMACDigest; delete HMACDigestSize;
        std::string paddedResult = "0000000000" + std::to_string(result);
        return paddedResult.substr(paddedResult.length() - tOTP.digits);
    }
}
