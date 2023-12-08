#pragma once
#include <memory>
#include <vector>
#include "utils.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Node.hpp"

NS_SPECTRUM_BEGIN

class SpriteBatch : public Node {
  public:
    SpriteBatch();

    virtual void update(float dt) override;
    virtual void draw() override;

    inline std::vector<Rectf>& getRects() { return m_rects; }
    void addRect(const Rectf& rect);

    inline void setTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }
    inline std::shared_ptr<Texture> getTexture() { return m_texture; }

    inline void setShader(std::shared_ptr<Shader> shader);
    inline std::shared_ptr<Shader> getShader() { return m_shader; }

    inline const Col3u& getColor() const { return m_color; }
    inline void setColor(const Col3u& col) { m_color = col; }

    inline void setShouldRebuild(bool val) { m_shouldRebuild = val; }

  private:
    void rebuild();

    std::vector<Rectf> m_rects;
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Shader> m_shader;
    Col3u m_color;
    bool m_shouldRebuild;
};

NS_SPECTRUM_END