#include "TextureFrame.hpp"
#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

TextureFrame::TextureFrame(std::shared_ptr<Texture> texture, const Rectf& rect, bool rotated) : m_texture(texture), m_rotated(rotated) {
    m_size = WindowManager::get()->pixelsToSize(rotated ? Vec2f {rect.h, rect.w} : Vec2f {rect.w, rect.h});

    if (rotated)
        m_texCoords = {Vec2f {rect.x + rect.w, rect.y}, Vec2f {rect.x, rect.y}, Vec2f {rect.x + rect.w, rect.y + rect.h},
                       Vec2f {rect.x, rect.y + rect.h}};
    else
        m_texCoords = {Vec2f {rect.x, rect.y}, Vec2f {rect.x, rect.y + rect.h}, Vec2f {rect.x + rect.w, rect.y},
                       Vec2f {rect.x + rect.w, rect.y + rect.h}};

    auto texSize = texture->getVec2inPixels();

    for (auto& pos : m_texCoords) {
        pos.x /= texSize.w;
        pos.y /= texSize.h;
    }
}

NS_SPECTRUM_END