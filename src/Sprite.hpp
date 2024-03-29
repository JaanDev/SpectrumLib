#pragma once
#include "utils.hpp"
#include "Node.hpp"
#include "Texture.hpp"
#include "TextureFrame.hpp"
#include "Shader.hpp"

NS_SPECTRUM_BEGIN

struct BlendFunc {
    GLenum src;
    GLenum dst;
};

class SPL_API Sprite : public Node {
  public:
    Sprite(const std::string& path);
    Sprite(std::shared_ptr<Texture> texture);
    Sprite(std::shared_ptr<TextureFrame> frame);
    ~Sprite();

    void setTexture(std::shared_ptr<Texture> tex);
    void setTextureFrame(std::shared_ptr<TextureFrame> frame);
    inline std::shared_ptr<Texture> getTexture() const { return m_texture; }
    inline std::shared_ptr<TextureFrame> getTextureFrame() const { return m_frame; };

    inline Col3u getColor() const { return m_color; }
    inline void setColor(const Col3u& color) { m_color = color; }

    void setBlendFunc(const BlendFunc& func);
    inline const BlendFunc& getBlendFunc() const { return m_blendFunc; }

    // оверрайдаем draw чтобы отрисовать текстуру
    virtual void draw() override;

    inline std::shared_ptr<Shader> getShader() const { return m_shader; }
    void setShader(std::shared_ptr<Shader> shader);

  protected:
    void makeVBO();
    void init();

    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<TextureFrame> m_frame;
    Col3u m_color;
    Rectf m_texCoords;
    std::shared_ptr<Shader> m_shader;
    BlendFunc m_blendFunc;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_colUniform;
};

NS_SPECTRUM_END