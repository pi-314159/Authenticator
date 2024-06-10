// Author:       pi-314159@GitHub
// License:      MIT
// Last updated: 2024-06-10

#include <tools/file_io.h>

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

    bool File_Io::WriteBinary(std::string& binaryFileContent, unsigned char* iV, unsigned int iVSize) {
        std::ofstream writeBinaryFileHandle(filePath, std::ios::binary);
        writeBinaryFileHandle.write((char*)iV, iVSize);
        writeBinaryFileHandle.write(binaryFileContent.c_str(), binaryFileContent.size());
        writeBinaryFileHandle.close();
        return true;
    }

    bool File_Io::DeleteFile() {
        bool ret = true;
        try {
            std::filesystem::remove(filePath);
        }
        catch (...) {
            ret = false;
        }
        return ret;
    }
}