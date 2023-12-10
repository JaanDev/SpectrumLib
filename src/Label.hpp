#pragma once
#include <string>
#include "utils.hpp"
#include "Node.hpp"
#include "FontManager.hpp"
#include "SpriteBatch.hpp"

NS_SPECTRUM_BEGIN

class Label : public SpriteBatch {
  public:
    // fontID это то, что указывали при загрузке в FontManager
    Label(const std::string& text, const std::string& fontID);
    Label(const std::string& text, const Font& font);

    void setText(const std::string& text);
    inline const std::string& getText() const { return m_text; }

    inline std::string getFontID() const { return m_fontID; }
    inline const Font& getFont() const { return m_font; }
    void setFont(const std::string& fontID);
    void setFont(const Font& font);

    inline TextAlignmentH getHorizontalAlignment() const { return m_textAlignmentH; }
    void setHorizontalAlignment(TextAlignmentH alignment);

    inline TextAlignmentV getVerticalAlignment() const { return m_textAlignmentV; }
    void setVerticalAlignment(TextAlignmentV alignment);

    // 0.f (like by default) => not used
    inline float getMaxWidth() const { return m_maxWidth; }
    void setMaxWidth(float maxW);

  protected:
    void rebuild();

    std::string m_text;
    std::string m_fontID;
    Font m_font;
    TextAlignmentH m_textAlignmentH;
    TextAlignmentV m_textAlignmentV;
    float m_maxWidth;
};

NS_SPECTRUM_END