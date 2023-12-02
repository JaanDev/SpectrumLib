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

    if (!stream.is_open()) {
        logE("Failed to load file {}!", absPath.string());
        return;
    }

    stream.seekg(0, stream.end);
    size_t len = stream.tellg();
    stream.seekg(0, stream.beg);
    byteVector.reserve(len);
    byteVector.insert(byteVector.begin(), std::istream_iterator<uint8_t>(stream), std::istream_iterator<uint8_t>());

    stbtt_fontinfo fontInfo;

    if (!stbtt_InitFont(&fontInfo, byteVector.data(), 0)) {
        logE("Failed to init font {}!", path.filename().string());
        return;
    }

    Sizei size = {1024, 1024};
    std::vector<stbtt_packedchar> charData(0x5D);
    // std::vector<stbtt_bakedchar> charData(fontInfo.numGlyphs - fontInfo.fontstart);
    std::vector<uint8_t> pixels(size.w * size.h);

    // stbtt_BakeFontBitmap(fontInfo.data, 0, lineHeight, pixels.data(), size.w, size.h, fontInfo.fontstart, fontInfo.numGlyphs,
    // charData.data());
    stbrp_context someCtx = {.x = 0, .y = 0, .height = 1024, .width = 1024, .bottom_y = 0};
    stbtt_pack_context packCtx {.h_oversample = 1,
                                .height = 1024,
                                .nodes = nullptr,
                                .pack_info = &someCtx,
                                .padding = 2,
                                .pixels = pixels.data(),
                                .skip_missing = 1,
                                .stride_in_bytes = 1024,
                                .user_allocator_context = nullptr,
                                .v_oversample = 1,
                                .width = 1024};

    // stbtt_PackFontRange(&packCtx, fontInfo.data, 0, lineHeight, 0x410, 0x3F, charData.data());

    stbtt_pack_range ranges[2];

    ranges[0] = stbtt_pack_range {.font_size = lineHeight,
                                  .first_unicode_codepoint_in_range = 'a',
                                  .num_chars = 'z' - 'a' + 1,
                                  .chardata_for_range = new stbtt_packedchar['z' - 'a' + 1]};

    ranges[1] = stbtt_pack_range {.font_size = lineHeight,
                                  .first_unicode_codepoint_in_range = 0x410,
                                  .num_chars = 0x3F,
                                  .chardata_for_range = new stbtt_packedchar[0x3F]};

    stbtt_PackFontRanges(&packCtx, fontInfo.data, 0, ranges, 2);

    std::unordered_map<unsigned int, Glyph> glyphs;

    auto ratio = AppManager::instance()->getPointsToPixelsRatio();

    // for (unsigned int i = 0; i < charData.size(); i++) {
    //     glyphs.insert(
    //         std::make_pair(i, Glyph {.textureRect = Recti {charData[i].x0, charData[i].y0, charData[i].x1 - charData[i].x0,
    //                                                        charData[i].y1 - charData[i].y0},
    //                                  .xOffset = charData[i].xoff * ratio.x,
    //                                  .yOffset = charData[i].yoff * ratio.y,
    //                                  .xAdvance = charData[i].xadvance * ratio.x}));
    // }

    for (int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < ranges[i].num_chars; j++) {
            glyphs.insert(std::make_pair(
                j, Glyph {.textureRect = Recti {ranges[i].chardata_for_range[j].x0, ranges[i].chardata_for_range[j].y0,
                                                ranges[i].chardata_for_range[j].x1 - ranges[i].chardata_for_range[j].x0,
                                                ranges[i].chardata_for_range[j].y1 - ranges[i].chardata_for_range[j].y0},
                          .xOffset = ranges[i].chardata_for_range[j].xoff * ratio.x,
                          .yOffset = ranges[i].chardata_for_range[j].yoff * ratio.y,
                          .xAdvance = ranges[i].chardata_for_range[j].xadvance * ratio.x}));
        }
    }

    m_fonts[id] = Font {.lineHeight = lineHeight,
                        .base = 0.0f,
                        .fontAtlas = std::make_shared<Texture>(pixels.data(), Sizei {size.w, size.h}, GL_RED),
                        .glyphs = glyphs};
}

void FontManager::loadBitmapFont(const std::string& path, const std::string& id) {}

const Font& FontManager::getFont(const std::string& id) const {
    return m_fonts.at(id);
}

NS_SPECTRUM_END
