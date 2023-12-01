#define STB_TRUETYPE_IMPLEMENTATION

#include "FontManager.hpp"
#include "FileManager.hpp"
#include "AppManager.hpp"
#include <stb_truetype.h>
#include <fstream>
#include "logger.hpp"

NS_SPECTRUM_BEGIN

FontManager* FontManager::instance() {
    static auto instance = std::make_unique<FontManager>();
    return instance.get();
}

void FontManager::loadFont(const std::filesystem::path& path, const std::string& id, float lineHeight) {
    auto absPath = FileManager::instance()->fullPathForFile(path.string());
    if (!std::filesystem::exists(absPath)) {
        logE("Failed to load a texture from file {}", absPath.string());
        return;
    }

    std::ifstream stream(absPath, std::ios::binary);
    std::vector<uint8_t> byteVector;
    stream.unsetf(std::ios::skipws);

    if(!stream.is_open()){
        logE("Failed to load file {}!", absPath.string());
        return;
    }

    stream.seekg(0, stream.end);
    size_t len = stream.tellg();
    stream.seekg(0, stream.beg);
    byteVector.reserve(len);
    byteVector.insert(byteVector.begin(), std::istream_iterator<uint8_t>(stream), std::istream_iterator<uint8_t>());

    stbtt_fontinfo fontInfo;

    if(!stbtt_InitFont(&fontInfo, byteVector.data(), 0)){
        logE("Failed to init font {}!", path.filename().string());
        return;
    }

    Sizei size = {1024, 1024};
    std::vector<stbtt_bakedchar> charData(fontInfo.numGlyphs - fontInfo.fontstart);
    std::vector<uint8_t> pixels(size.w * size.h);

    stbtt_BakeFontBitmap(fontInfo.data, 0, lineHeight, pixels.data(), size.w, size.h, fontInfo.fontstart, fontInfo.numGlyphs, charData.data());
    
    std::unordered_map<unsigned int, Glyph> glyphs;

    auto ratio = AppManager::instance()->getPointsToPixelsRatio();

    for(unsigned int i = 0; i < charData.size(); i++) {
        glyphs.insert(std::make_pair(i, Glyph {
            .textureRect = Recti {charData[i].x0, charData[i].y0, charData[i].x1 - charData[i].x0, charData[i].y1 - charData[i].y0},
            .xOffset = charData[i].xoff * ratio.x,
            .yOffset = charData[i].yoff * ratio.y,
            .xAdvance = charData[i].xadvance * ratio.x
        }));
    }
    
    m_fonts[id] = Font {
        .lineHeight = lineHeight,
        .base = 0.0f,
        .fontAtlas = std::make_shared<Texture>(pixels.data(), Sizei {size.w, size.h}, GL_RED),
        .glyphs = glyphs
    };
}

void FontManager::loadBitmapFont(const std::string& path, const std::string& id) {}

const Font& FontManager::getFont(const std::string& id) const {
    return m_fonts.at(id);
}

NS_SPECTRUM_END
