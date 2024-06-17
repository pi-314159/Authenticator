// Author:       pi-314159@GitHub
// License:      MIT

#ifndef TOOLS__STRING_H_
#define TOOLS__STRING_H_

#include <string>

namespace TOOLS {
    class String {
    public:
        bool Input(std::string& input, std::string prompt = "", bool getLine = false);

        template<typename T>
        bool FormatInput(std::string& input, T& output, char type = '0') {
            bool ret = false;

            // type: 0 string; 1 long long; 2 unsigned long long; 3 long double
            switch (type) {
            case '0':
                input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);
                ret = true;
                break;
            case '1':
                try {
                    output = std::stoll(input);
                    ret = true;
                }
                catch (...) {
                    ret = false;
                }
                break;
            case '2':
                try {
                    output = std::stoull(input);
                    ret = true;
                }
                catch (...) {
                    ret = false;
                }
                break;
            case '3':
                try {
                    output = std::stold(input);
                    ret = true;
                }
                catch (...) {
                    ret = false;
                }
                break;
            }
            return ret;
        }
    };
}

#endif
