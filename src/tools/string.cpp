// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#include <tools/string.h>

#include <iostream>
#include <limits>

namespace TOOLS {
    bool String::Input(std::string& input, std::string prompt, bool getLine) {
        input = "";
        if (prompt != "") {
            std::cout << prompt << " ";
        }
        while (input.empty()) {
            if (getLine) {
                if (getline(std::cin >> std::ws, input)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else {
                    return false;
                }
            }
            else {
                if (std::cin >> std::ws >> input) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
}
