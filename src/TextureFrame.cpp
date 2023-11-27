#include "TextureFrame.hpp"
#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

TextureFrame::TextureFrame(std::shared_ptr<Texture> texture, Recti rect, bool rotated) : m_texture(texture), m_rect(rect), m_rotated(rotated) {}

Sizef TextureFrame::getSize() {
    return AppManager::instance()->pixelsToSize({(float)m_rect.w, (float)m_rect.h});
}

NS_SPECTRUM_END