#pragma once
#include <string>
#include <string_view>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class Shader {
  public:
    Shader();
    ~Shader();

    bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    bool loadFromString(std::string_view vertexShaderSrc, std::string_view fragmentShaderSrc);

    void use();

    inline GLuint getShaderProgram() const { return m_shaderProgram; }

  private:
    GLuint m_shaderProgram;
    GLint m_mvpLocation;
};

NS_SPECTRUM_END