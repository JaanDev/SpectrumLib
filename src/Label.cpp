#include "Label.hpp"
#include "AppManager.hpp"
#include <utf8.h>

NS_SPECTRUM_BEGIN

Label::Label(const std::string& text, const std::string& fontID)
    : m_text(text), m_fontID(fontID), m_font(FontManager::instance()->getFont(fontID)), m_textAlignmentH(TextAlignmentH::Center),
      m_textAlignmentV(TextAlignmentV::Center), m_maxWidth(0.f), SpriteBatch(m_font.fontAtlas){
    rebuild();
}

Label::Label(const std::string& text, const Font& font)
    : m_text(text), m_fontID(""), m_font(font), m_textAlignmentH(TextAlignmentH::Center),
      m_textAlignmentV(TextAlignmentV::Center), m_maxWidth(0.f), SpriteBatch(m_font.fontAtlas) {
    rebuild();
}

void Label::setText(const std::string& text) {
    m_text = text;
    rebuild();
}

void Label::setFont(const std::string& fontID) {
    m_fontID = fontID;
    m_font = FontManager::instance()->getFont(fontID);
    rebuild();
}

void Label::setFont(const Font& font) {
    m_fontID = "";
    m_font = font;
    rebuild();
}

void Label::setHorizontalAlignment(TextAlignmentH alignment) {
    m_textAlignmentH = alignment;
    rebuild();
}

void Label::setVerticalAlignment(TextAlignmentV alignment) {
    m_textAlignmentV = alignment;
    rebuild();
}

void Label::setMaxWidth(float maxW) {
    m_maxWidth = maxW;
    rebuild();
}

void Label::rebuild() {
    setTexture(this->getFont().fontAtlas);
    Vec2f pos = this->getPos();

    auto it = m_text.begin();
    auto end = m_text.end();
    auto ratio = AppManager::instance()->getPointsToPixelsRatio();
    auto size = getFont().fontAtlas->getSizeInPixels();
    while (it != m_text.end()) {
        auto cp = utf8::next(it, end);
        
        if (!m_font.glyphs.contains(cp))
            continue;

        const auto& glyph = m_font.glyphs[cp];
        
        addRect({
            .rect = {pos.x + glyph.xOffset, pos.y + glyph.yOffset, (float)glyph.textureRect.w * ratio.x, (float)glyph.textureRect.h * ratio.y},
            .texCoords = {
                .x = glyph.textureRect.x / (float)size.w,
                .y = glyph.textureRect.y / (float)size.h,
                .w = glyph.textureRect.w / (float)size.w,
                .h = glyph.textureRect.h / (float)size.h
            }
        });

        pos.x += glyph.xAdvance;
    }
}

NS_SPECTRUM_END
