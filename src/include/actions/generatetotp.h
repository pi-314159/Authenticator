// Author:       pi-314159@GitHub
// License:      MIT

#ifndef ACTIONS__GENERATETOTP_H_
#define ACTIONS__GENERATETOTP_H_

#include <totp.h>

namespace ACTIONS {
    std::string GenerateTotp(tOTP_object& tOTP);
}

#endif
