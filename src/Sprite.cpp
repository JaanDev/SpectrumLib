#include "Sprite.hpp"

#include "TextureManager.hpp"
#include "logger.hpp"
#include "ShaderManager.hpp"

NS_SPECTRUM_BEGIN

Sprite::Sprite(const std::string& path)
    : Node(), m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}), m_vao(0), m_texCoords({0.0f, 0.0f, 1.0f, 1.0f}) {
    m_texture = std::make_shared<Texture>(path);
    m_boundingBox = m_texture->getSize();

    init();
}

Sprite::Sprite(std::shared_ptr<Texture> texture)
    : Node(), m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}), m_texture(texture),
      m_vao(0), m_texCoords({0.0f, 0.0f, 1.0f, 1.0f}) {
    m_boundingBox = m_texture->getSize();

    init();
}

Sprite::Sprite(std::shared_ptr<TextureFrame> frame) 
    : Node(), m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}), m_frame(frame), 
      m_vao(0) {
    
    m_texture = frame->getTexture();
    m_boundingBox = frame->getSize();

    auto rect = frame->getRect();
    auto size = frame->getTexture()->getSizeInPixels();
    
    m_texCoords = {
        (float)rect.x / size.w,
        (float)rect.y / size.h,
        (float)rect.w / size.w,
        (float)rect.h / size.h
    };

    init();
}

void Sprite::init() {
    m_shader = ShaderManager::instance()->getShader("sprite-shader");
    makeVBO();
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Sprite::setTexture(std::shared_ptr<Texture> tex) {
    m_texture = tex;
    m_boundingBox = tex->getSize();

    // clang-format off
    const float vertices[] = {
        // positions                               texCoords
        0.0f,            0.0f,            0.0f,    0.0f, 0.0f,
        0.0f,            m_boundingBox.h, 0.0f,    0.0f, 1.0f,
        m_boundingBox.w, 0.0f,            0.0f,    1.0f, 0.0f,
        m_boundingBox.w, m_boundingBox.h, 0.0f,    1.0f, 1.0f,
    };
    // clang-format on

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::setBlendFunc(const BlendFunc& func) {}

void Sprite::draw() {
    m_shader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->getTextureID());

    glUniform3f(m_colUniform, m_color.r / 255.f, m_color.g / 255.f, m_color.b / 255.f);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void Sprite::makeVBO() {
    // clang-format off
    const float vertices[] = {
        // positions                               texCoords
        0.0f,            0.0f,            0.0f,    m_texCoords.x,                 m_texCoords.y,
        0.0f,            m_boundingBox.h, 0.0f,    m_texCoords.x,                 m_texCoords.y + m_texCoords.h,
        m_boundingBox.w, 0.0f,            0.0f,    m_texCoords.x + m_texCoords.w, m_texCoords.y,
        m_boundingBox.w, m_boundingBox.h, 0.0f,    m_texCoords.x + m_texCoords.w, m_texCoords.y + m_texCoords.h,
    };

    const unsigned int indices[] = {
        0, 1, 2, 3
    };
    // clang-format on

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUniform1i(glGetUniformLocation(m_shader->getShaderProgram(), "tex"), 0);
    m_colUniform = glGetUniformLocation(m_shader->getShaderProgram(), "col");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_vao = VAO;
    m_vbo = VBO;
    m_ebo = EBO;
}

NS_SPECTRUM_END
