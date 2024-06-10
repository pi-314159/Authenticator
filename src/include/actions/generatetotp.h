// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#ifndef ACTIONS__GENERATETOTP_H_
#define ACTIONS__GENERATETOTP_H_

#include <totp.h>

namespace ACTIONS {
	std::string GenerateTOTP(tOTP_object& tOTP);
}

#endif
