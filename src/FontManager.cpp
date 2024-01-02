#define STB_TRUETYPE_IMPLEMENTATION

#include "FontManager.hpp"
#include "FileManager.hpp"
#include "AppManager.hpp"
#include <stb_truetype.h>
#include <fstream>
#include "logger.hpp"

NS_SPECTRUM_BEGIN

FontManager* FontManager::get() {
    static auto instance = FontManager();
    return &instance;
}

void FontManager::loadFont(const std::string& path, const std::string& id, float lineHeight,
                           const std::vector<FontRange>& ranges) {
    auto absPath = FileManager::get()->fullPathForFile(path);
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
    size_t len = (size_t)stream.tellg();
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

    const auto padding = 2;

    stbtt_pack_range* ttRanges = new stbtt_pack_range[ranges.size()];

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

    stbtt_pack_context packCtx1 = {.padding = padding, .skip_missing = 1, .h_oversample = 1, .v_oversample = 1};
    auto totalChars = 0u;
    for (const auto& range : ranges) {
        totalChars += range.endCP - range.startCP + 1;
    }
    stbrp_rect* rects = new stbrp_rect[totalChars];
    auto numRects = stbtt_PackFontRangesGatherRects(&packCtx1, &fontInfo, ttRanges, ranges.size(), rects);
    auto area = 0u;
    for (auto i = 0; i < numRects; i++) {
        area += rects[i].w * rects[i].h;
    }

    auto atlasW = (int)(sqrt(area) * 1.2f);

    auto atlasH = 0;
    int px, py;
    px = py = 0;
    for (auto i = 0u; i < numRects; i++) {
        const auto& rect = rects[i];

        if (px + rect.w > atlasW) {
            px = 0;
            py = atlasH;
        }

        px += rect.w;
        if (py + rect.h > atlasH)
            atlasH = py + rect.h;
    }
    atlasH += padding;

    uint8_t* pixels = new uint8_t[atlasW * atlasH];
    memset(pixels, NULL, atlasW * atlasH);

    stbrp_context someCtx = {.width = atlasW, .height = atlasH, .x = 0, .y = 0, .bottom_y = 0};
    stbtt_pack_context packCtx {.user_allocator_context = nullptr,
                                .pack_info = &someCtx,
                                .width = atlasW,
                                .height = atlasH,
                                .stride_in_bytes = atlasW,
                                .padding = padding,
                                .skip_missing = 1,
                                .h_oversample = 1,
                                .v_oversample = 1,
                                .pixels = pixels,
                                .nodes = nullptr};

    stbtt_PackFontRanges(&packCtx, fontInfo.data, 0, ttRanges, ranges.size());

    std::unordered_map<unsigned int, Glyph> glyphs;

    auto ratio = AppManager::get()->getPointsToPixelsRatio();

    for (auto i = 0u; i < ranges.size(); i++) {
        for (auto j = 0u; j < ttRanges[i].num_chars; j++) {
            const auto& chr = ttRanges[i].chardata_for_range[j];

            glyphs[ttRanges[i].first_unicode_codepoint_in_range + j] =
                Glyph {.textureRect = Recti {chr.x0, chr.y0, chr.x1 - chr.x0, chr.y1 - chr.y0},
                       .xOffset = chr.xoff * ratio.x,
                       .yOffset = chr.yoff * ratio.y,
                       .xAdvance = chr.xadvance * ratio.x};
        }
    }

    int iascent, idescent, ilineGap;
    iascent = idescent = ilineGap = 0;
    auto scale = stbtt_ScaleForPixelHeight(&fontInfo, lineHeight);
    stbtt_GetFontVMetrics(&fontInfo, &iascent, &idescent, &ilineGap);
    float ascent = iascent * scale;
    float descent = idescent * scale;
    float lineGap = ilineGap * scale;

    m_fonts[id] = Font {.lineHeight = (ascent - descent + lineGap) * ratio.y,
                        .base = lineHeight,
                        .fontAtlas = std::make_shared<Texture>(pixels, Sizei {atlasW, atlasH}, GL_RED),
                        .glyphs = glyphs,
                        .shaderName = "ttf-shader"};

    for (auto i = 0u; i < ranges.size(); i++) {
        delete[] ttRanges[i].chardata_for_range;
    }

    delete[] bytes;
    delete[] ttRanges;
    delete[] rects;
    delete[] pixels;
}

void FontManager::loadBitmapFont(const std::string& path, const std::string& id) {
    auto absPath = FileManager::get()->fullPathForFile(path);
    if (!std::filesystem::exists(absPath)) {
        logE("Failed to load a texture from file {}", absPath.string());
        return;
    }

    auto ratio = AppManager::get()->getPointsToPixelsRatio();

    Font font;
    font.shaderName = "sprite-shader";
    std::ifstream stream(absPath);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.find("info") != std::string::npos)
            continue;

        if (line.find("common") != std::string::npos) {
            int varsParsed = sscanf_s(line.c_str(), "common lineHeight=%f base=%f", &font.lineHeight, &font.base);
            if (varsParsed < 2) {
                logE("Can't parse common line in file {}", absPath.string());
                return;
            }
            font.lineHeight *= ratio.y;
            font.base *= ratio.y;
            continue;
        }

        if (auto it = line.find("file"); it != std::string::npos && font.fontAtlas == nullptr) {
            line.erase(0, it);
            char* filename = new char[129];

            int varsParsed = sscanf_s(line.c_str(), "file=\"%128[^\"]\"", filename);
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
            int varsParsed = sscanf_s(line.c_str(), "chars count=%i", &charscount);

            if (varsParsed < 1)
                logW("Can't parse chars count {}", absPath.string());
            else
                font.glyphs.reserve(charscount);
            continue;
        }

        if (line.find("char ") != std::string::npos) {
            unsigned int id;
            Glyph glyph;

            int varsParsed = sscanf_s(line.c_str(), "char id=%i x=%i y=%i width=%i height=%i xoffset=%f yoffset=%f xadvance=%f",
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

void FontManager::addFont(const Font& font, const std::string& id) {
    m_fonts[id] = font;
}

Font& FontManager::getFont(const std::string& id) {
    return m_fonts[id];
}

NS_SPECTRUM_END
