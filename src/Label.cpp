#include "Label.hpp"

NS_SPECTRUM_BEGIN

Label::Label(const std::string& text, const std::string& fontID)
    : m_text(text), m_fontID(fontID), m_font(FontManager::instance()->getFont(fontID)), m_textAlignmentH(TextAlignmentH::Center),
      m_textAlignmentV(TextAlignmentV::Center), m_maxWidth(0.f) {
    rebuild();
}

Label::Label(const std::string& text, const Font& font)
    : m_text(text), m_fontID(""), m_font(font), m_textAlignmentH(TextAlignmentH::Center),
      m_textAlignmentV(TextAlignmentV::Center), m_maxWidth(0.f) {
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

void Label::rebuild() {}

NS_SPECTRUM_END
