// Author:       pi-314159@GitHub
// License:      MIT

#include <actions/add.h>
#include <actions/generatetotp.h>
#include <tools/file_io.h>
#include <tools/vectortostring.h>
#include <tools/string.h>

#include <chrono>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    std::cout << "=========================== PI Authenticator ===========================\n"
        "= Last Updated:      2024-07-03                                        =\n"
        "= License:           MIT                                               =\n"
        "= GitHub Repository: github.com/pi-314159/Authenticator                =\n"
        "========================================================================\n\n" << std::endl;

    std::string action = "l";
    std::vector<tOTP_object> tOTPObjects;
    unsigned char key[32] = {'P', 'I', '-', '3', '1', '4', '1', '5', '9', '@', 'G', 'H'};
    std::string* accountsFilePassword = new std::string();
    TOOLS::Crypto crypto;

    auto accountsFilePath = std::make_unique<std::string>((argc > 1) ? argv[1] : "Accounts");
    auto fileIo = std::make_unique<TOOLS::File_Io>(accountsFilePath);
    auto str = std::make_unique_for_overwrite<TOOLS::String>();

    if (std::filesystem::exists(*accountsFilePath) && std::filesystem::file_size(*accountsFilePath) != 0) {
        *accountsFilePath = "TPlease enter your password:";
    }
    else {
        *accountsFilePath = "FCreating `" + *accountsFilePath + "`... Secrets will be stored here.\nPlease enter a password between 6 and 20 characters to protect the file:";
    }

    str->Input(*accountsFilePassword, accountsFilePath->substr(1));
    while (true) {
        // Test password length
        while ((accountsFilePassword->length() < 6) || (accountsFilePassword->length() > 20)) {
            if ((*accountsFilePath)[0] == 'T') {
                str->Input(*accountsFilePassword, "INCORRECT password! Please enter your password:");
            }
            else {
                str->Input(*accountsFilePassword, "Password does NOT meet the requirement! Please enter a new password:");
            }
        }

        if ((*accountsFilePath)[0] == 'F') {
            // Test whether passwords match
            std::string tmpPassword;
            str->Input(tmpPassword, "Please re-type your password:");
            if (tmpPassword == *accountsFilePassword) {
                action = "a";
                for (short int i = 12; i < 32; ++i) {
                    key[i] = tmpPassword[i % tmpPassword.length()];
                }
                break;
            }
            else {
                str->Input(*accountsFilePassword, "Passwords do NOT match. Please enter a new password:");
            }
        }
        else {
            // Open and decrypt an existing file
            for (short int i = 12; i < 32; ++i) {
                key[i] = (*accountsFilePassword)[i % accountsFilePassword->length()];
            }
            std::string fileContents;
            auto encryptedFileContents = std::make_unique_for_overwrite<std::string>();
            fileIo->ReadBinary(*encryptedFileContents);
            unsigned long long int fileContentsSize = 0;
            unsigned char* iV = new unsigned char[16];
            for (short int i = 0; i < 16; ++i) {
                iV[i] = (*encryptedFileContents)[i];
            }
            (*encryptedFileContents).erase(0, 16);
            crypto.Aes(key, iV, *encryptedFileContents, fileContents, fileContentsSize, false);
            encryptedFileContents.reset();
            delete[] iV;
            if ((fileContents[0] == 'O') && (fileContents[1] == 'K')) {
                fileContents.erase(0, 2);
                try {
                    std::stringstream ssContents(fileContents);
                    std::string fileLine, lineElement;
                    while (std::getline(ssContents, fileLine, '\n'))
                    {
                        std::stringstream ssLine(fileLine);
                        tOTP_object tOTPInstance;
                        unsigned short int i = 0;
                        while (std::getline(ssLine, lineElement, '\r')) {
                            switch (i) {
                            case 0:
                                tOTPInstance.tag = lineElement;
                                break;
                            case 1:
                                tOTPInstance.secret = lineElement;
                                break;
                            case 2:
                                tOTPInstance.period = std::stoul(lineElement);
                                break;
                            case 3:
                                tOTPInstance.alg = lineElement;
                                break;
                            case 4:
                                tOTPInstance.digits = std::stoi(lineElement);
                                break;
                            }
                            ++i;
                        }
                        tOTPObjects += tOTPInstance;
                    }
                    break;
                }
                catch (...) {
                    std::cout << "\nERROR: Corrupted file!!!" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    exit(1);
                }
            }
            else {
                str->Input(*accountsFilePassword, "INCORRECT password! Please enter your password:");
            }
        }
    }
    delete accountsFilePassword;
    accountsFilePath.reset();
    unsigned long long int tOTPObjectsSize = tOTPObjects.size();
    std::cout << '\n' << std::endl;

    unsigned long long int selectedOTPIndex = 0;
    std::string optionsAvailable = "aclq";
    // action: [a] add; [d] delete; [l] list; [q] quit; [g] generate an OTP; [c] change password
    while (action[0] != 'q') {
        STARTLOOP:
        if (action[0] == 'g') {
            std::cout << "OTP: " << ACTIONS::GenerateTotp(tOTPObjects[selectedOTPIndex], crypto) << '\n' << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else if (action[0] == 'c') {
            auto accountsFilePassword = std::make_unique_for_overwrite<std::string>();
            str->Input(*accountsFilePassword, "Please enter a new password between 6 and 20 characters:");
            while ((accountsFilePassword->length() < 6) || (accountsFilePassword->length() > 20)) {
                str->Input(*accountsFilePassword, "Password does NOT meet the requirement! Please enter a new password:");
            }
            std::string tmpPassword;
            str->Input(tmpPassword, "Please re-type your password:");
            if (tmpPassword == *accountsFilePassword) {
                for (short int i = 12; i < 32; ++i) {
                    key[i] = tmpPassword[i % tmpPassword.length()];
                }
                accountsFilePassword.reset();
                auto toWrite = std::make_unique<std::string>("OK" + TOOLS::VectorToString(tOTPObjects));
                fileIo->WriteBinary(*toWrite, crypto, key);
                toWrite.reset();
                std::cout << "Changed.\n" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else {
                std::cout << "Passwords do NOT match. ";
                accountsFilePassword.reset();
                goto STARTLOOP;
            }
        }
        else if (action[0] == 'l') {
            if (tOTPObjectsSize > 0) {
                unsigned long long tOTPObjectsSizeWidth = log10(tOTPObjectsSize + 1) + 3;
                for (unsigned long long int j = 0; j < tOTPObjectsSize; ++j) {
                    auto tempStr = "[" + std::to_string(1 + j) + "]";
                    std::cout << std::setw(tOTPObjectsSizeWidth) << tempStr << "          " << tOTPObjects[j].tag << std::endl;
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "Empty list.\n" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if (action[0] == 'd') {
            if (tOTPObjectsSize > 1) {
                tOTPObjects.erase(tOTPObjects.begin() + selectedOTPIndex);
                action[0] = 'l';
                auto toWrite = std::make_unique<std::string>("OK" + TOOLS::VectorToString(tOTPObjects));
                fileIo->WriteBinary(*toWrite, crypto, key);
                toWrite.reset();
            }
            else {
                tOTPObjects.clear();
                fileIo->DeleteFile();
                action[0] = 'a';
            }
            --tOTPObjectsSize;
            std::cout << "Deleted.\n" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            goto STARTLOOP;
        } else if (action[0] == 'a') {
            ACTIONS::Add(tOTPObjects);
            action[0] = 'l';
            ++tOTPObjectsSize;
            auto toWrite = std::make_unique<std::string>("OK" + TOOLS::VectorToString(tOTPObjects));
            fileIo->WriteBinary(*toWrite, crypto, key);
            toWrite.reset();
            std::cout << "Added.\n" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            goto STARTLOOP;
        }
        
        str->Input(action, "Select from the following options:\nGenerate an OTP    [number]\nAdd                [a]\nDelete             [d[number]]\nList               [l]\nChange password    [c]\nQuit               [q]:\nEnter your choice:");
        if ((action[0] == 'd') || (action[0] == 'D')) {
            action.erase(0, 1);
            action = ' ' + action;
        }
        if (str->FormatInput(action, selectedOTPIndex, '2')) {
            if ((selectedOTPIndex > tOTPObjectsSize) || (selectedOTPIndex == 0)) {
                std::cout << "\n\nERROR: Out of range. ";
                action = "i";
            }
            else {
                if (action[0] == ' ') {
                    str->Input(action, "Are your sure to delete [" + std::to_string(selectedOTPIndex) + "] " + tOTPObjects[selectedOTPIndex - 1].tag + "? [Y/n]");
                    action = ((action[0] == 'Y') || (action[0] == 'y')) ? "d" : "i";
                }
                else {
                    action = "g";
                }
                --selectedOTPIndex;
            }
        }
        else {
            action[0] = std::tolower(action[0]);
            if (!(optionsAvailable.find(action[0]) != std::string::npos)) {
                std::cout << "\n\nERROR: Invalid option. ";
                action = "i";
            }
        }
    }

    fileIo.reset(); str.reset();
    return 0;
}
