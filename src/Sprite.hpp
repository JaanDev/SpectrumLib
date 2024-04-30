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
    // Sprite(const std::string& path);
    // Sprite(std::shared_ptr<Texture> texture);
    // Sprite(std::shared_ptr<TextureFrame> frame);

    static std::shared_ptr<Sprite> create();
    static std::shared_ptr<Sprite> create(const std::string& texturePath);
    static std::shared_ptr<Sprite> create(std::shared_ptr<Texture> texture);
    static std::shared_ptr<Sprite> create(std::shared_ptr<TextureFrame> frame);

    Sprite(std::shared_ptr<TextureFrame> frame);
    Sprite();
    ~Sprite();

    void setTextureFrame(std::shared_ptr<TextureFrame> frame);
    inline std::shared_ptr<TextureFrame> getTextureFrame() const { return m_frame; };

    inline Col3u getColor() const { return m_color; }
    inline void setColor(const Col3u& color) { m_color = color; }

    void setBlendFunc(const BlendFunc& func);
    inline const BlendFunc& getBlendFunc() const { return m_blendFunc; }

    // override draw to render a texture
    virtual void draw() override;

    inline std::shared_ptr<Shader> getShader() const { return m_shader; }
    void setShader(std::shared_ptr<Shader> shader);

    // 0 to 1
    inline float getOpacity() const { return m_opacity; }
    // 0 to 1
    void setOpacity(float opacity);

  protected:
    void makeVBO();

    std::shared_ptr<TextureFrame> m_frame;
    std::shared_ptr<Shader> m_shader;
    Col3u m_color;
    float m_opacity;
    BlendFunc m_blendFunc;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_colUniform;
    GLuint m_opacityUniform;
};

NS_SPECTRUM_END