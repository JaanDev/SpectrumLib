#pragma once
#include <string>
#include <string_view>
#include "utils.hpp"
#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

class SPL_API Shader {
  public:
    Shader();
    ~Shader();

    bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    bool loadFromString(std::string_view vertexShaderSrc, std::string_view fragmentShaderSrc);

    inline void use() {
        glUseProgram(m_shaderProgram);
        glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &AppManager::get()->getCurMtx()[0][0]);
    }

    inline GLuint getShaderProgram() const { return m_shaderProgram; }
    inline GLuint getUniformLocation(const char* name) const { return glGetUniformLocation(m_shaderProgram, name); }

  private:
    GLuint m_shaderProgram;
    GLint m_mvpLocation;
};

NS_SPECTRUM_END