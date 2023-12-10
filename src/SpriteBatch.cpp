#include "SpriteBatch.hpp"

#include <numeric>
#include "logger.hpp"
#include "ShaderManager.hpp"

NS_SPECTRUM_BEGIN

SpriteBatch::SpriteBatch(std::shared_ptr<Texture> tex)
    : m_quads({}), m_texture(tex), m_color({255, 255, 255}), m_shouldRebuild(false), m_vao(0), m_vbo(0), m_ebo(0),
      m_indicesSize(0) {
    m_shader = ShaderManager::instance()->getShader("sprite-shader");
    glUniform1i(glGetUniformLocation(m_shader->getShaderProgram(), "tex"), 0);
    m_colUniform = glGetUniformLocation(m_shader->getShaderProgram(), "col");
}

SpriteBatch::~SpriteBatch() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void SpriteBatch::update(float dt) {
    if (m_shouldRebuild) {
        m_shouldRebuild = false;
        rebuild();
    }
}

void SpriteBatch::draw() {
    m_shader->use();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->getTextureID());

    glUniform3f(m_colUniform, m_color.r / 255.f, m_color.g / 255.f, m_color.b / 255.f);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glDisable(GL_BLEND);
}

void SpriteBatch::addRect(const BatchQuad& rect) {
    m_quads.push_back(rect);
    m_shouldRebuild = true;
}

void SpriteBatch::setShader(std::shared_ptr<Shader> shader) {
    m_shader = shader;
    glUniform1i(glGetUniformLocation(m_shader->getShaderProgram(), "tex"), 0);
    m_colUniform = glGetUniformLocation(m_shader->getShaderProgram(), "col");
}

void SpriteBatch::rebuild() {
    std::vector<float> vertices;

    for (const auto& quad : m_quads) {
        auto& rect = quad.rect;
        auto& tex = quad.texCoords;

        // clang-format off
        vertices.insert(vertices.end(), {
            rect.x,          rect.y,          0.f, tex.x,         tex.y,
            rect.x,          rect.y + rect.h, 0.f, tex.x,         tex.y + tex.h,
            rect.x + rect.w, rect.y,          0.f, tex.x + tex.w, tex.y,
            rect.x + rect.w, rect.y + rect.h, 0.f, tex.x + tex.w, tex.y + tex.h
        });
        // clang-format on
    }

    std::vector<unsigned int> indices;

    for (auto i = 0u; i < m_quads.size(); i++) {
        auto idx = i * 4;
        indices.insert(indices.end(), {idx, idx + 1, idx + 2, idx + 1, idx + 2, idx + 3});
    }

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_vao = VAO;
    m_vbo = VBO;
    m_ebo = EBO;
    m_indicesSize = indices.size();
}

NS_SPECTRUM_END
