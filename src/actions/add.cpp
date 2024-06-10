// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#include <actions/add.h>
#include <tools/string.h>

#include <memory>
#include <regex>

namespace ACTIONS {
	void Add(std::vector<tOTP_object>& tOTPObjects) {
		auto str = std::make_unique_for_overwrite<TOOLS::String>();
		std::string inputBuffer, tag, secret;
		char alg = '1';
		unsigned int period;
		unsigned short digits;
		while (inputBuffer.empty()) {
			str->Input(inputBuffer, "Please enter the issuer (e.g., GitHub), then hit Enter TWICE to proceed:", true);
			str->FormatInput(inputBuffer, inputBuffer);
		}
		tag = inputBuffer + "::";
		inputBuffer = "";
		while (inputBuffer.empty()) {
			str->Input(inputBuffer, "Please enter the account (e.g., user@example.com), \nthen hit Enter TWICE to proceed:", true);
			str->FormatInput(inputBuffer, inputBuffer);
		}
		tag += inputBuffer;
		inputBuffer = "";
		std::regex base32Pattern("[^a-zA-Z2-7]");
		while (inputBuffer.empty()) {
			str->Input(inputBuffer, "Please enter the secret:");
			str->FormatInput(inputBuffer, inputBuffer);
			inputBuffer = std::regex_replace(inputBuffer, base32Pattern, "");
		}
		secret = inputBuffer;
		std::transform(secret.begin(), secret.end(), secret.begin(), ::toupper);
		str->Input(inputBuffer, "Please enter the period (default 30):");
		if (str->FormatInput(inputBuffer, period, '2')) {
			if (period < 1) period = 30;
		}
		else {
			period = 30;
		}
		str->Input(inputBuffer, "Please select the hash algorithm:\n[1] SHA-1\n[2] SHA-256\n[3] SHA-384\n[5] SHA-512\nEnter your choice (default 1):");
		if (inputBuffer == "2") {
			alg = '2';
		} else if (inputBuffer == "3") {
			alg = '3';
		} else if (inputBuffer == "5") {
			alg = '5';
		}
		str->Input(inputBuffer, "Please enter the digits (between 6 - 10, default 6):");
		if (str->FormatInput(inputBuffer, digits, '2')) {
			if ((digits < 6) || digits > 10) digits = 6;
		}
		else {
			digits = 6;
		}
		tOTP_object tOTPInstance;
		tOTPInstance.tag = tag; tOTPInstance.secret = secret; tOTPInstance.period = period; tOTPInstance.alg = alg; tOTPInstance.digits = digits;
		tOTPObjects += tOTPInstance;
		return;
	}
}