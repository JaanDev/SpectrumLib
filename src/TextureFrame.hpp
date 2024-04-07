#pragma once
#include <string>
#include "utils.hpp"
#include "Texture.hpp"
#include <memory>
#include <array>

NS_SPECTRUM_BEGIN

class SPL_API TextureFrame {
  public:
    TextureFrame(std::shared_ptr<Texture> texture, Rectf rect, bool rotated);

    // in points
    inline const Sizef& getSize() const { return m_size; }
    inline const std::array<Vec2f, 4>& getTexCoords() const { return m_texCoords; };
    inline std::shared_ptr<Texture> getTexture() { return m_texture; }

  private:
    std::shared_ptr<Texture> m_texture;
    std::array<Vec2f, 4> m_texCoords;
    Sizef m_size; // points
    bool m_rotated;
};

NS_SPECTRUM_END