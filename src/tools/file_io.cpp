// Author:       pi-314159@GitHub
// License:      MIT

#include <tools/file_io.h>
#include <tools/generateiv.h>

#include <filesystem>
#include <fstream>

namespace TOOLS {
    File_Io::File_Io(std::unique_ptr<std::string>& s) {
        filePath = *s;
    }

    bool File_Io::ReadBinary(std::string& binaryFileContent) {
        std::ifstream readBinaryFileHandle(filePath, std::ios::binary);
        binaryFileContent = std::string{ std::istreambuf_iterator<char>(readBinaryFileHandle), std::istreambuf_iterator<char>() };
        readBinaryFileHandle.close();
        return true;
    }

    bool File_Io::WriteBinary(std::string& binaryFileContent, TOOLS::Crypto& crypto, unsigned char key[], unsigned int iVSize) {
        unsigned char* iV = new unsigned char[16];
        GenerateIv(iV);
        std::string encryptedContents;
        unsigned long long int encryptedContentsSize = 0;
        crypto.Aes(key, iV, binaryFileContent, encryptedContents, encryptedContentsSize);
        std::ofstream writeBinaryFileHandle(filePath, std::ios::binary);
        writeBinaryFileHandle.write((char*)iV, iVSize);
        writeBinaryFileHandle.write(encryptedContents.c_str(), encryptedContentsSize);
        writeBinaryFileHandle.close();
        delete[] iV;
        return true;
    }

    bool File_Io::DeleteFile() {
        return std::filesystem::remove(filePath);
    }
}