#pragma once
#include <filesystem>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class FileManager {
  public:
    static FileManager* instance();
    FileManager();

    std::filesystem::path fullPathForFile(const std::string& name);
    void addSearchPath(const std::filesystem::path& path);
    void removeSearchPath(const std::filesystem::path& path);
    void removeAllSearchPaths();
    const std::vector<std::filesystem::path>& getSearchPaths() const { return m_searchPaths; }

    // Returns the path to the root of the disk on which the application is running
    std::filesystem::path getRootPath();
    std::filesystem::path getAppPath();
    std::filesystem::path getTempPath();

  private:
    std::vector<std::filesystem::path> m_searchPaths;
};

NS_SPECTRUM_END