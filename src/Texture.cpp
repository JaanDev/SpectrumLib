#include "Texture.hpp"

#include "AppManager.hpp"
#include "stb_image.h"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

Texture::Texture(const std::string& path) : m_format(0), m_size({0, 0}), m_textureID(0) {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int bpp;
    auto data = stbi_load(path.c_str(), &m_size.w, &m_size.h, &bpp, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.w, m_size.h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        logE("Failed to load a texture from file {}", path);
    }
    stbi_image_free(data);
}

Texture::Texture(uint8_t* data, unsigned int dataLen) : m_format(0), m_size({0, 0}), m_textureID(0) {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int bpp;
    auto imgData = stbi_load_from_memory(data, dataLen, &m_size.w, &m_size.h, &bpp, 0);
    if (imgData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.w, m_size.h, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        logE("Failed to load a texture from memory");
    }
    stbi_image_free(imgData);
}

Sizef Texture::getSize() {
    return AppManager::instance()->pixelsToSize({static_cast<float>(m_size.w), static_cast<float>(m_size.h)});
}

void Texture::setTexParams(const TexParams& params) {
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.magFilter);
}

NS_SPECTRUM_END
