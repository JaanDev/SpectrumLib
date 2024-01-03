#pragma once
#include <string>
#include "utils.hpp"
#include "Texture.hpp"
#include <memory>

NS_SPECTRUM_BEGIN

class SPL_API TextureFrame {
  public:
    TextureFrame(std::shared_ptr<Texture> texture, Recti rect, bool rotated);

    inline std::shared_ptr<Texture> getTexture() { return m_texture; }

    // in pixels
    inline Recti getRect() const { return m_rect; }

    // in points
    Sizef getSize();

  private:
    std::shared_ptr<Texture> m_texture;
    Recti m_rect;
    bool m_rotated;
};

NS_SPECTRUM_END