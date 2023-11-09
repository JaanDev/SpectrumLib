#include "FileManager.hpp"

#include "logger.hpp"

NS_SPECTRUM_BEGIN

FileManager* FileManager::instance() {
    static auto instance = std::make_unique<FileManager>();
    return instance.get();
}

std::filesystem::path FileManager::fullPathForFile(const std::string& name) {
    for (const auto& searchPath : m_searchPaths) {
        for (auto file : std::filesystem::directory_iterator(searchPath)) {
            auto filePath = file.path();
            if (filePath.has_filename() && filePath.filename().string() == name)
                return std::filesystem::canonical(filePath);
        }
    }

    logE("Failed to find a full path for file {}", name);

    return name;
}

void FileManager::addSearchPath(const std::filesystem::path& path) {
    m_searchPaths.push_back(std::filesystem::canonical(path));
}

void FileManager::removeSearchPath(const std::filesystem::path& path) {
    if (auto it = std::find(m_searchPaths.begin(), m_searchPaths.end(), path); it != m_searchPaths.end())
        m_searchPaths.erase(it);
}

void FileManager::removeAllSearchPaths() {
    m_searchPaths.clear();
}

std::filesystem::path FileManager::getRootPath() {
    return std::filesystem::current_path().root_path();
}

std::filesystem::path FileManager::getAppPath() {
    return std::filesystem::current_path();
}

std::filesystem::path FileManager::getTempPath() {
    return std::filesystem::temp_directory_path();
}

NS_SPECTRUM_END