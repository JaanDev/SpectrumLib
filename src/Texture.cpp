#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "AppManager.hpp"
#include "logger.hpp"
#include "FileManager.hpp"

NS_SPECTRUM_BEGIN

Texture::Texture(const std::string& path) : m_format(0), m_size({0, 0}), m_textureID(0) {
    auto absPath = FileManager::instance()->fullPathForFile(path);
    if (!std::filesystem::exists(absPath)) {
        logE("Failed to load a texture from file {}", absPath.string());
        return;
    }

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int bpp;
    auto data = stbi_load(absPath.string().c_str(), &m_size.w, &m_size.h, &bpp, 4);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.w, m_size.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        logE("Failed to load a texture from file {}", absPath.string());
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0); // unbind current texture to prevent accidental editing
}

Texture::Texture(uint8_t* data, unsigned int dataLen) : m_format(0), m_size({0, 0}), m_textureID(0) {
    if (!data || dataLen == 0) {
        logE("Failed to load a texture from memory (invalid input: data = 0x{:08X}, dataLen = 0x{:08X})", (uintptr_t)data,
             dataLen);
        return;
    }

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

    glBindTexture(GL_TEXTURE_2D, 0); // unbind current texture to prevent accidental editing
}

Texture::Texture(uint8_t* data, Sizei size, int format = GL_RGB) : m_format(0), m_size(size), m_textureID(0) {
    if (!data || (m_size.w * m_size.h) == 0) {
        logE("Failed to load a texture from memory (invalid input: data = 0x{:08X}, dataLen = 0x{:08X})", (uintptr_t)data,
             (m_size.w * m_size.h));
        return;
    }

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_size.w, m_size.h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0); // unbind current texture to prevent accidental editing
}


Texture::~Texture() {
    glDeleteTextures(1, &m_textureID);
}

Sizef Texture::getSize() {
    return AppManager::instance()->pixelsToSize(m_size.to<float>());
}

void Texture::setTexParams(const TexParams& params) {
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.magFilter);
    glBindTexture(GL_TEXTURE_2D, 0); // unbind current texture to prevent accidental editing
}

NS_SPECTRUM_END
