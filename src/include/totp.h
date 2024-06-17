// Author:       pi-314159@GitHub
// License:      MIT

#ifndef TOTP_H_
#define TOTP_H_

#include <string>
#include <vector>

struct tOTP_object {
    std::string tag;
    std::string secret;
    unsigned int period;
    std::string alg;
    unsigned short digits;
};

template<typename T>
void operator+=(std::vector<T>& v, T& item) {
    v.push_back(item);
    return;
}

#endif
