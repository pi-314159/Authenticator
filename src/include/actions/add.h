// Author:       pi-314159@GitHub
// License:      MIT

#ifndef ACTIONS__ADD_H_
#define ACTIONS__ADD_H_

#include <totp.h>
#include <tools/crypto.h>

namespace ACTIONS {
    std::string Add(std::vector<tOTP_object>& tOTPObjects, TOOLS::Crypto& crypto);
}

#endif
