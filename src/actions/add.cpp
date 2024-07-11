// Author:       pi-314159@GitHub
// License:      MIT

#include <actions/add.h>
#include <tools/string.h>

#include <iostream>
#include <ranges>
#include <regex>

namespace ACTIONS {
    std::string Add(std::vector<tOTP_object>& tOTPObjects, TOOLS::Crypto& crypto) {
        std::map<std::string_view, std::string_view> urlEncode {
            {"%20", " "}, {"%2B", "+"}, {"%2F", "/"},
            {"%3A", ":"}, {"%3D", "="},
            {"%40", "@"}};

        auto addStrObj = std::make_unique_for_overwrite<TOOLS::String>();
        std::string inputBuffer;
        std::cout << "Please input the TOTP URI beginning with \"otpauth\", then hit Enter TWICE to proceed:" << std::endl;
        while (inputBuffer.empty()) {
            addStrObj->Input(inputBuffer, "", true);
            addStrObj->FormatInput(inputBuffer, inputBuffer);
        }

        if (inputBuffer.starts_with("otpauth://totp/")) {
            inputBuffer = inputBuffer.substr(15);
            for (auto& X: urlEncode) {
                addStrObj->StringReplace(inputBuffer, X.first, X.second);
            }
            addStrObj.reset();
        }
        else {
            addStrObj.reset();
            return "ERROR: Bad URI.";
        }

        std::string tag = inputBuffer.substr(0, inputBuffer.find('?'));
        if (tag.empty()) return "ERROR: The label could not be found in the URI.";

        inputBuffer = inputBuffer.substr(inputBuffer.find('?') + 1);
        std::map<std::string, std::string> totp;
        for (auto word: inputBuffer | std::views::split('&')) {
            auto tempStr = word | std::ranges::to<std::string>();
            totp[tempStr.substr(0, tempStr.find('='))] = tempStr.substr(tempStr.find('=') + 1);
        }

        if (!totp.contains("secret")) return "ERROR: The secret could not be found in the URI.";
        std::regex base32Pattern("[^a-zA-Z2-7]");
        std::string secret = std::regex_replace(totp["secret"], base32Pattern, "");
        if (secret.empty()) return "ERROR: The secret could not be found in the URI.";
        std::transform(secret.begin(), secret.end(), secret.begin(), ::toupper);

        unsigned int period = 30;
        if (totp.contains("period")) {
            if (std::atol(totp["period"].c_str()) > 0) {
                period = std::atol(totp["period"].c_str());
            }
            else {
                return "ERROR: Invalid period in the URI.";
            }
        }

        unsigned short digits = 6;
        if (totp.contains("digits")) {
            if ((std::atoi(totp["digits"].c_str()) > 5) && (std::atoi(totp["digits"].c_str()) < 11)) {
                digits = std::atoi(totp["digits"].c_str());
            }
            else {
                return "ERROR: Invalid digits in the URI.";
            }
        }

        std::string alg = "sha1";
        if (totp.contains("algorithm")) {
            if (crypto.hashAlgorithms.contains(totp["algorithm"])) {
                alg = totp["algorithm"];
            }
            else {
                return "ERROR: Invalid hash algorithm in the URI.";
            }
        }

        if (totp.contains("issuer") && (!tag.starts_with(totp["issuer"]))) tag = totp["issuer"] + "::" + tag;

        tOTP_object tOTPInstance;
        tOTPInstance.tag = tag; tOTPInstance.secret = secret; tOTPInstance.period = period; tOTPInstance.alg = alg; tOTPInstance.digits = digits;
        tOTPObjects += tOTPInstance;

        return "O";
    }
}