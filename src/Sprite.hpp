#pragma once
#include "utils.hpp"
#include "Node.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

NS_SPECTRUM_BEGIN

struct BlendFunc {
    GLenum src;
    GLenum dst;
};

class Sprite : public Node {
  public:
    Sprite(const std::string& path);
    Sprite(std::shared_ptr<Texture> texture);

    void setTexture(std::shared_ptr<Texture> tex);
    inline std::shared_ptr<Texture> getTexture() const { return m_texture; }

    inline Col3u getColor() const { return m_color; }
    inline void setColor(const Col3u& color) { m_color = color; }

    void setBlendFunc(const BlendFunc& func);
    inline const BlendFunc& getBlendFunc() const { return m_blendFunc; }

    // оверрайдаем draw чтобы отрисовать текстуру
    virtual void draw() override;

    inline std::shared_ptr<Shader> getShader() const { return m_shader; }
    inline void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; }

  protected:
    std::shared_ptr<Texture> m_texture;
    Col3u m_color;
    std::shared_ptr<Shader> m_shader;
    BlendFunc m_blendFunc;
};

NS_SPECTRUM_END