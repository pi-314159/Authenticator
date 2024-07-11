// Author:       pi-314159@GitHub
// License:      MIT

#include <tools/string.h>

#include <iostream>
#include <limits>
#include <ranges>

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

    void String::StringReplace(std::string& str, std::string_view pattern, std::string_view replacement) {
#if defined(__clang__)
        // Clang doesn't support `views::join_with`.
        size_t pos = 0;
        std::string search = pattern | std::ranges::to<std::string>();
        std::string replace = replacement | std::ranges::to<std::string>();
        while ((pos = str.find(search, pos)) != std::string::npos) {
            str.replace(pos, search.length(), replace);
            pos += replace.length();
        }
#else
        str = str | std::views::split(pattern) | std::views::join_with(replacement) | std::ranges::to<std::string>();
#endif
        return;
    }
}
