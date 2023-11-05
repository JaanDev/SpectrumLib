#pragma once
#include <memory>
#include <unordered_map>
#include "utils.hpp"
#include "types.hpp"
#include "Texture.hpp"

NS_SPECTRUM_BEGIN

struct Glyph {
    Recti textureRect;
    int xOffset; // на сколько смещается буква вправо относительно позиции курсора
    int yOffset; // на сколько смещается буква вниз относительно позиции курсора
    int xAdvance; // на сколько смещать курсор вправо после отрисовки буквы
};

struct Font {
    float lineHeight;
    float base;
    std::shared_ptr<Texture> fontAtlas;
    std::unordered_map<unsigned int, Glyph> glyphs;
};

class FontManager {
  public:
    static FontManager* instance();

    void loadTTF(const std::string& path, const std::string& id);
    void loadBitmapFont(const std::string& path, const std::string& id);

    const Font& getFont(const std::string& id) const;

  private:
    std::unordered_map<std::string, Font> m_fonts;
};

NS_SPECTRUM_END