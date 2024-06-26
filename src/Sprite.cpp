#include "Sprite.hpp"

#include "TextureManager.hpp"
#include "logger.hpp"
#include "ShaderManager.hpp"

NS_SPECTRUM_BEGIN

std::shared_ptr<Sprite> Sprite::create() {
    return std::make_shared<Sprite>();
}

std::shared_ptr<Sprite> Sprite::createWithTexName(const std::string& texturePath) {
    auto tex = TextureManager::get()->getTexture(texturePath);

    if (!tex)
        return nullptr;

    return Sprite::create(std::make_shared<TextureFrame>(tex, Rectf {0, 0, (float)tex->getVec2inPixels().w, (float)tex->getVec2inPixels().h}, false));
}

std::shared_ptr<Sprite> Sprite::createWithFrameName(const std::string& frameName) {
    return Sprite::create(TextureManager::get()->getTextureFrame(frameName));
}

std::shared_ptr<Sprite> Sprite::create(std::shared_ptr<Texture> texture) {
    if (!texture)
        return nullptr;

    return Sprite::create(
        std::make_shared<TextureFrame>(texture, Rectf {0, 0, (float)texture->getVec2inPixels().w, (float)texture->getVec2inPixels().h}, false));
}

std::shared_ptr<Sprite> Sprite::create(std::shared_ptr<TextureFrame> frame) {
    if (!frame)
        return nullptr;

    auto ret = std::make_shared<Sprite>();
    ret->setTextureFrame(frame);
    return ret;
}

Sprite::Sprite()
    : m_frame(nullptr), m_opacity(1.0f), m_color({255, 255, 255}), m_opacityUniform(0), m_blendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}), m_vao(0),
      m_vbo(0), m_ebo(0), m_colUniform(0) {
    setShader(ShaderManager::get()->getShader("sprite-shader"));
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Sprite::setTextureFrame(std::shared_ptr<TextureFrame> frame) {
    if (!frame)
        return;

    if (!m_frame)
        setupBuffers();

    m_frame = frame;
    setBoundingBox(frame->getSize());

    const auto& texCoords = frame->getTexCoords();

    // clang-format off
    const float vertices[] = {
        // positions                      texCoords
        0.0f,            0.0f,            texCoords[0].x, texCoords[0].y,
        0.0f,            m_boundingBox.h, texCoords[1].x, texCoords[1].y,
        m_boundingBox.w, 0.0f,            texCoords[2].x, texCoords[2].y,
        m_boundingBox.w, m_boundingBox.h, texCoords[3].x, texCoords[3].y
    };

    // const unsigned int indices[] = {
    //     0, 1, 2, 3
    // };
    // clang-format on

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Sprite::setBlendFunc(const BlendFunc& func) {
    m_blendFunc = func;
}

void Sprite::draw() {
    if (!m_frame || !m_shader)
        return;

    m_shader->use();

    glEnable(GL_BLEND);
    glBlendFunc(m_blendFunc.src, m_blendFunc.dst);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_frame->getTexture()->getTextureID());

    glUniform3f(m_colUniform, m_color.r / 255.f, m_color.g / 255.f, m_color.b / 255.f);
    glUniform1f(m_opacityUniform, m_opacity);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
}

void Sprite::setShader(std::shared_ptr<Shader> shader) {
    m_shader = shader;
    glUniform1i(m_shader->getUniformLocation("tex"), 0);
    m_colUniform = m_shader->getUniformLocation("col");
    m_opacityUniform = m_shader->getUniformLocation("opacity");
}

// void Sprite::makeVBO() {
//     const auto& texCoords = m_frame->getTexCoords();

//     // clang-format off
//     const float vertices[] = {
//         // positions                      texCoords
//         0.0f,            0.0f,            texCoords[0].x, texCoords[0].y,
//         0.0f,            m_boundingBox.h, texCoords[1].x, texCoords[1].y,
//         m_boundingBox.w, 0.0f,            texCoords[2].x, texCoords[2].y,
//         m_boundingBox.w, m_boundingBox.h, texCoords[3].x, texCoords[3].y
//     };

//     const unsigned int indices[] = {
//         0, 1, 2, 3
//     };
//     // clang-format on

//     unsigned int VBO, VAO, EBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     // position attribute
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     // texture coord attribute
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     glBindVertexArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//     m_vao = VAO;
//     m_vbo = VBO;
//     m_ebo = EBO;
// }

void Sprite::setupBuffers() {
    const unsigned int indices[] = {0, 1, 2, 3};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_vao = VAO;
    m_vbo = VBO;
    m_ebo = EBO;
}

NS_SPECTRUM_END
