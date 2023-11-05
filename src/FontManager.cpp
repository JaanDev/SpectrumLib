#include "FontManager.hpp"

NS_SPECTRUM_BEGIN

FontManager* FontManager::instance() {
    static auto instance = std::make_unique<FontManager>();
    return instance.get();
}

void FontManager::loadTTF(const std::string& path, const std::string& id) {}

void FontManager::loadBitmapFont(const std::string& path, const std::string& id) {}

const Font& FontManager::getFont(const std::string& id) const {
    return m_fonts.at(id);
}

NS_SPECTRUM_END
