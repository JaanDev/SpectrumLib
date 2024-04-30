#pragma once
#include <string>
#include "utils.hpp"
#include "Node.hpp"
#include "FontManager.hpp"
#include "SpriteBatch.hpp"

NS_SPECTRUM_BEGIN

class SPL_API Label : public SpriteBatch {
  public:
    // fontID это то, что указывали при загрузке в FontManager
    Label(const std::string& text, const std::string& fontID, TextAlignment alignment = TextAlignment::Left, float maxWidth = 0.f);
    Label(const std::string& text, const Font& font, TextAlignment alignment = TextAlignment::Left, float maxWidth = 0.f);

    void setText(const std::string& text);
    inline const std::string& getText() const { return m_text; }

    inline std::string getFontID() const { return m_fontID; }
    inline const Font& getFont() const { return m_font; }
    void setFont(const std::string& fontID);
    void setFont(const Font& font);

    inline TextAlignment getAlignment() const { return m_textAlignment; }
    void setAlignment(TextAlignment alignment);

    // 0.f (like by default) => not used
    inline float getMaxWidth() const { return m_maxWidth; }
    void setMaxWidth(float maxW);

  protected:
    void rebuild();
    std::vector<std::string> separateText();

    std::string m_text;
    std::string m_fontID;
    Font m_font;
    float m_maxWidth;
    TextAlignment m_textAlignment;
};

NS_SPECTRUM_END