#include "Shader.hpp"

#include <glm/glm.hpp>
#include <fstream>
#include "FileManager.hpp"
#include "logger.hpp"
#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

Shader::Shader() : m_shaderProgram(0), m_mvpLocation(0) {}

Shader::~Shader() {
    glDeleteProgram(m_shaderProgram);
}

bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
    auto vertexFullPath = FileManager::get()->fullPathForFile(vertexPath);
    auto fragFullPath = FileManager::get()->fullPathForFile(fragmentPath);

    std::ifstream vertStream(vertexFullPath, std::ios::in);
    if (!vertStream) {
        logE("Failed to open a stream for file {}", vertexFullPath.string());
        return false;
    }

    std::string vertData;
    vertStream >> vertData;

    vertStream.close();

    std::ifstream fragStream(fragFullPath, std::ios::in);
    if (!fragStream) {
        logE("Failed to open a stream for file {}", fragFullPath.string());
        return false;
    }

    std::string fragData;
    fragStream >> fragData;

    fragStream.close();

    return loadFromString(vertData, fragData);
}

bool Shader::loadFromString(std::string_view vertexShaderSrc, std::string_view fragmentShaderSrc) {
    auto vertShader = glCreateShader(GL_VERTEX_SHADER);
    auto vrtSrc = vertexShaderSrc.data();
    glShaderSource(vertShader, 1, &vrtSrc, nullptr);
    glCompileShader(vertShader);

    int success;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        logE("Failed to compile a vertex shader: \"{}\"", infoLog);
        return false;
    }

    auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    auto fragSrc = fragmentShaderSrc.data();
    glShaderSource(fragShader, 1, &fragSrc, nullptr);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        logE("Failed to compile a fragment shader: \"{}\"", infoLog);
        return false;
    }

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertShader);
    glAttachShader(m_shaderProgram, fragShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        logE("Failed to link a shader program: \"{}\"", infoLog);
        return false;
    }

    glDetachShader(m_shaderProgram, vertShader);
    glDetachShader(m_shaderProgram, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    glUseProgram(m_shaderProgram);
    m_mvpLocation = glGetUniformLocation(m_shaderProgram, "mvp");

    return true;
}

void Shader::use() {
    glUseProgram(m_shaderProgram);
    glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &AppManager::get()->getMatrix()[0][0]);
}

NS_SPECTRUM_END
