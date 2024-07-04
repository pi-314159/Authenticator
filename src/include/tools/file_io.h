// Author:       pi-314159@GitHub
// License:      MIT

#ifndef TOOLS__FILE_IO_H_
#define TOOLS__FILE_IO_H_

#include <tools/crypto.h>

#include <memory>

namespace TOOLS {
    class File_Io {
    protected:
        std::string filePath;
    public:
        File_Io(std::unique_ptr<std::string>& s);
        bool ReadBinary(std::string& binaryFileContent);
        bool WriteBinary(std::string& binaryFileContent, TOOLS::Crypto& crypto, unsigned char key[], unsigned int iVSize = 16);
        bool DeleteFile();
    };
}

#endif
