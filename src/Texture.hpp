#pragma once
#include <string>
#include "utils.hpp"
#include "types.hpp"

NS_SPECTRUM_BEGIN

struct TexParams {
    GLuint minFilter; // minification filter
    GLuint magFilter; // magnification filter
    GLuint wrapS;
    GLuint wrapT;
};

class Texture {
  public:
    // from file
    Texture(const std::string& path);
    // from memory, dont forget to free `data` after loading the tex
    Texture(uint8_t* data, unsigned int dataLen);

    // in points
    Sizef getSize();
    inline const Sizei& getSizeInPixels() const { return m_size; }
    inline int getFormat() const { return m_format; }
    inline GLuint getTextureID() const { return m_textureID; }

    void setTexParams(const TexParams& params);

  private:
    int m_format;
    Sizei m_size; // in pixels
    GLuint m_textureID;
};

NS_SPECTRUM_END