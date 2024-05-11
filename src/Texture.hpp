#pragma once
#include <string>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

struct TexParams {
    GLuint minFilter = GL_LINEAR_MIPMAP_LINEAR; // minification filter
    GLuint magFilter = GL_LINEAR;               // magnification filter
    GLuint wrapS = GL_REPEAT;                   // wrap x
    GLuint wrapT = GL_REPEAT;                   // wrap y
};

class SPL_API Texture {
  public:
    // from file
    Texture(const std::string& path);
    // from memory, dont forget to free `data` after loading the tex
    Texture(uint8_t* data, unsigned int dataLen);
    Texture(uint8_t* data, Vec2i size, int format);

    ~Texture();

    // in points
    Vec2f getSize();
    inline const Vec2i& getVec2inPixels() const { return m_size; }
    inline int getFormat() const { return m_format; }
    inline GLuint getTextureID() const { return m_textureID; }

    void setTexParams(const TexParams& params);

  private:
    int m_format; // TODO: make use of this
    Vec2i m_size; // in pixels
    GLuint m_textureID;
};

NS_SPECTRUM_END