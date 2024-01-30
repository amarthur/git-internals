#pragma once

#include <filesystem>

const std::filesystem::path GIT_DIR = ".ugit";
const std::filesystem::path OBJ_DIR = GIT_DIR / "objects";

namespace Data {
void init();
std::string hashObject(const std::string& filePath,
                       const std::string& type_ = "blob");
void getObject(const std::string& oid, const std::string& expected = "blob");
}  // namespace Data

void makeDir(const std::filesystem::path& dirPath);
std::string getOid(const std::string& filePath);