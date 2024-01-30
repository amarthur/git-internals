#include "data.hpp"

#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace Data {
void init() {
    makeDir(GIT_DIR);
    makeDir(OBJ_DIR);
}

std::string hashObject(const std::string& filePath, const std::string& type_) {
    std::string oid = getOid(filePath);
    std::filesystem::path hashObjFile = OBJ_DIR / oid;

    std::ifstream sourceFile(filePath, std::ios::binary);
    std::ofstream destinationFile(hashObjFile, std::ios::binary);

    destinationFile.write(type_.c_str(), type_.length());
    destinationFile.put('\0');
    destinationFile << sourceFile.rdbuf();

    return oid;
}

void getObject(const std::string& oid, const std::string& expected) {
    std::filesystem::path oidPath = OBJ_DIR / oid;
    std::ifstream f(oidPath);

    std::string type_;
    char currentChar;
    while (f.get(currentChar) && currentChar != '\0') type_ += currentChar;

    if (!expected.empty()) assert(type_ == expected && "Error: type mismatch");

    std::cout << f.rdbuf() << std::endl;
}

}  // namespace Data

void makeDir(const std::filesystem::path& dirPath) {
    try {
        std::filesystem::create_directory(dirPath);
    } catch (std::exception& e) {
        std::cerr << "Error creating " << dirPath.string() << "directory."
                  << e.what() << std::endl;
    }
}

std::string getOid(const std::string& filePath) {
    // Calculate SHA1 hash and transform it to HEX
    std::string oid;
    CryptoPP::SHA1 hash;
    CryptoPP::HexEncoder* hexenc =
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(oid));
    CryptoPP::HashFilter* hfilter = new CryptoPP::HashFilter(hash, hexenc);
    CryptoPP::FileSource f(filePath.c_str(), true, hfilter);
    return oid;
}
