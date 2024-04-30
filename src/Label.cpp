#include "Label.hpp"
#include "AppManager.hpp"
#include "ShaderManager.hpp"
#include <utf8.h>

#include "logger.hpp"

NS_SPECTRUM_BEGIN

Label::Label(const std::string& text, const std::string& fontID, TextAlignment alignment, float maxWidth)
    : m_text(text), m_fontID(fontID), m_font(FontManager::get()->getFont(fontID)), m_textAlignment(alignment), m_maxWidth(maxWidth) {
    m_texture = m_font.fontAtlas;
    rebuild();
}

Label::Label(const std::string& text, const Font& font, TextAlignment alignment, float maxWidth)
    : m_text(text), m_fontID(""), m_font(font), m_textAlignment(alignment), m_maxWidth(maxWidth) {
    m_texture = m_font.fontAtlas;
    rebuild();
}

void Label::setText(const std::string& text) {
    m_text = text;
    rebuild();
}

void Label::setFont(const std::string& fontID) {
    m_fontID = fontID;
    m_font = FontManager::get()->getFont(fontID);
    rebuild();
}

void Label::setFont(const Font& font) {
    m_fontID.clear();
    m_font = font;
    rebuild();
}

void Label::setAlignment(TextAlignment alignment) {
    m_textAlignment = alignment;
    rebuild();
}

void Label::setMaxWidth(float maxW) {
    m_maxWidth = maxW;
    rebuild();
}

void Label::rebuild() {
    setTexture(m_font.fontAtlas);
    m_quads.clear();
    setShader(ShaderManager::get()->getShader(m_font.shaderName == nullptr ? "sprite-shader" : m_font.shaderName));

    auto lines = separateText();

    auto ratio = AppManager::get()->getPointsToPixelsRatio();
    auto size = m_font.fontAtlas->getSizeInPixels();
    Sizef box = {0, m_font.base};
    Vec2f pos = {0, m_font.base};

    for (const auto& line : lines) {
        pos.x = 0;
        int lineQuadCount = 0;

        auto it = line.begin();
        auto end = line.end();
        while (it != line.end()) {
            auto cp = utf8::next(it, end);

            if (!m_font.glyphs.contains(cp))
                continue;

            const auto& glyph = m_font.glyphs[cp];

            Rectf glyphRect = {pos.x + glyph.xOffset, pos.y + glyph.yOffset, (float)glyph.textureRect.w * ratio.x,
                               (float)glyph.textureRect.h * ratio.y};

            if (auto y2 = glyphRect.y + glyphRect.h; y2 > box.h)
                box.h = y2;

            addRect(BatchQuad {.rect = glyphRect,
                               .texCoords = {.x = glyph.textureRect.x / (float)size.w,
                                             .y = glyph.textureRect.y / (float)size.h,
                                             .w = glyph.textureRect.w / (float)size.w,
                                             .h = glyph.textureRect.h / (float)size.h}});

            pos.x += glyph.xAdvance;
            if (pos.x > box.w)
                box.w = pos.x;
            lineQuadCount++;
        }

        float lineWidth = pos.x;

        if (m_textAlignment == TextAlignment::Center) {
            auto lineOffset = lineWidth / 2.f;
            auto quadLen = m_quads.size();
            for (auto i = 0u; i < lineQuadCount; i++) {
                m_quads[quadLen - 1 - i].rect.x -= lineWidth / 2.f;
                // m_quads[quadLen - 1 - i].rect.x -= lineOffset;
            }
        } else if (m_textAlignment == TextAlignment::Right) {
            auto quadLen = m_quads.size();
            for (auto i = 0u; i < lineQuadCount; i++) {
                m_quads[quadLen - 1 - i].rect.x -= lineWidth;
            }
        }

        pos.y += m_font.lineHeight;
    }

    if (m_textAlignment == TextAlignment::Right) {
        for (auto& quad : m_quads) {
            quad.rect.x += box.w;
        }
    } else if (m_textAlignment == TextAlignment::Center) {
        for (auto& quad : m_quads) {
            quad.rect.x += box.w / 2.f;
        }
    }

    setBoundingBox(box);
}

std::vector<std::string> Label::separateText() {
    std::vector<std::string> ret;

    if (m_maxWidth > 0.f) {
        auto ratio = AppManager::get()->getPointsToPixelsRatio();

        std::string current;
        float currentWidth = 0.f;
        auto it = m_text.begin();
        auto end = m_text.end();
        while (it != m_text.end()) {
            auto cp = utf8::next(it, end);

            if (cp == '\n') {
                ret.push_back(current);
                current.clear();
                currentWidth = 0.f;
                continue;
            }

            if (!m_font.glyphs.contains(cp))
                continue;

            const auto& glyph = m_font.glyphs[cp];
            if (currentWidth + glyph.textureRect.w > m_maxWidth && current.length() > 0) {
                ret.push_back(current);
                current.clear();
                currentWidth = 0.f;
            }

            currentWidth += glyph.xOffset + glyph.xAdvance;
            utf8::append(cp, current);
        }

        ret.push_back(current);
    } else if (m_text.find('\n') != std::string::npos) {
        std::string current;

        auto it = m_text.begin();
        auto end = m_text.end();
        while (it != m_text.end()) {
            auto cp = utf8::next(it, end);

            if (cp == '\n') {
                ret.push_back(current);
                current.clear();
                continue;
            }

            utf8::append(cp, current);
        }

        ret.push_back(current);
    } else {
        ret.push_back(m_text);
    }

    return ret;
}

NS_SPECTRUM_END
