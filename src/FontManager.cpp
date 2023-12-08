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

void FontManager::loadFont(const std::string& path, const std::string& id, float lineHeight,
                           const std::vector<FontRange>& ranges) {
    auto absPath = FileManager::instance()->fullPathForFile(path);
    if (!std::filesystem::exists(absPath)) {
        logE("Failed to load file {}!", absPath.string());
        return;
    }

    std::ifstream stream(absPath, std::ios::binary);

    if (!stream) {
        logE("Failed to load file {}!", absPath.string());
        return;
    }

    stream.seekg(0, std::ios::end);
    size_t len = stream.tellg();
    stream.seekg(0, std::ios::beg);

    auto bytes = new uint8_t[len];
    stream.read((char*)bytes, len);
    stream.close();

    stbtt_fontinfo fontInfo;

    if (!stbtt_InitFont(&fontInfo, bytes, 0)) {
        logE("Failed to init font {}!", absPath.string());
        delete[] bytes;
        return;
    }

    Sizei size = {1024, 1024};
    std::vector<uint8_t> pixels(size.w * size.h);

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

    stbtt_pack_range ttRanges[ranges.size()];

    for (auto i = 0u; i < ranges.size(); i++) {
        const auto& range = ranges[i];
        auto numChars = range.endCP - range.startCP + 1;

        auto chars = new stbtt_packedchar[numChars];
        memset(chars, 0, numChars * sizeof(stbtt_packedchar)); // this is done to prevent random values for characters that are
                                                               // not present in the font but still used by the user

        ttRanges[i] = stbtt_pack_range {.font_size = lineHeight,
                                        .first_unicode_codepoint_in_range = range.startCP,
                                        .num_chars = numChars,
                                        .chardata_for_range = chars};
    }

    stbtt_PackFontRanges(&packCtx, fontInfo.data, 0, ttRanges, ranges.size());

    std::unordered_map<unsigned int, Glyph> glyphs;

    auto ratio = AppManager::instance()->getPointsToPixelsRatio();

    for (const auto& range : ttRanges) {
        for (auto i = 0u; i < range.num_chars; i++) {
            const auto& chr = range.chardata_for_range[i];

            glyphs[range.first_unicode_codepoint_in_range + i] =
                Glyph {.textureRect = Recti {chr.x0, chr.y0, chr.x1 - chr.x0, chr.y1 - chr.y0},
                       .xAdvance = chr.xadvance * ratio.x,
                       .xOffset = chr.xoff * ratio.x,
                       .yOffset = chr.yoff * ratio.y};
        }
    }

    m_fonts[id] = Font {.lineHeight = lineHeight,
                        .base = 0.0f,
                        .fontAtlas = std::make_shared<Texture>(pixels.data(), Sizei {size.w, size.h}, GL_RED),
                        .glyphs = glyphs};

    for (const auto& range : ttRanges) {
        delete[] range.chardata_for_range;
    }

    delete[] bytes;
}

void FontManager::loadBitmapFont(const std::string& path, const std::string& id) {
    auto absPath = FileManager::instance()->fullPathForFile(path);
    if (!std::filesystem::exists(absPath)) {
        logE("Failed to load a texture from file {}", absPath.string());
        return;
    }

    auto ratio = AppManager::instance()->getPointsToPixelsRatio();

    Font font;
    std::ifstream stream(absPath);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.find("info") != std::string::npos)
            continue;

        if (line.find("common") != std::string::npos) {
            int varsParsed = sscanf(line.c_str(), "common lineHeight=%f base=%f", &font.lineHeight, &font.base);
            if (varsParsed < 2) {
                logE("Can't parse common line in file {}", absPath.string());
                return;
            }
            continue;
        }

        if (auto it = line.find("file"); it != std::string::npos && font.fontAtlas == nullptr) {
            line.erase(0, it);
            char* filename = new char[129];

            int varsParsed = sscanf(line.c_str(), "file=\"%128[^\"]\"", filename);
            if (varsParsed < 1) {
                logE("Can't parse page line in file {}", absPath.string());
                return;
            }

            font.fontAtlas = std::make_shared<Texture>(filename);

            delete[] filename;
            continue;
        }

        if (line.find("chars count") != std::string::npos) {
            int charscount;
            int varsParsed = sscanf(line.c_str(), "chars count=%i", &charscount);

            if (varsParsed < 1)
                logW("Can't parse chars count {}", absPath.string());
            else
                font.glyphs.reserve(charscount);
            continue;
        }

        if (line.find("char ") != std::string::npos) {
            unsigned int id;
            Glyph glyph;

            int varsParsed = sscanf(line.c_str(), "char id=%i x=%i y=%i width=%i height=%i xoffset=%f yoffset=%f xadvance=%f",
                                    &id, &glyph.textureRect.x, &glyph.textureRect.y, &glyph.textureRect.w, &glyph.textureRect.h,
                                    &glyph.xOffset, &glyph.yOffset, &glyph.xAdvance);

            if (varsParsed < 8) {
                logW("Can't parse char id {} in file {}", id, absPath.string());
                continue;
            }

            glyph.xAdvance *= ratio.x;
            glyph.xOffset *= ratio.x;
            glyph.yOffset *= ratio.y;

            font.glyphs[id] = glyph;
        }
    }

    m_fonts[id] = font;
}

const Font& FontManager::getFont(const std::string& id) const {
    return m_fonts.at(id);
}

NS_SPECTRUM_END
