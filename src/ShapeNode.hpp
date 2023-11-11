#pragma once
#include <functional>
#include "utils.hpp"
#include "Node.hpp"

NS_SPECTRUM_BEGIN

class ShapeNode : public Node {
  public:
    ShapeNode();
    virtual void draw() override;

    void setDrawCallback(std::function<void()> callback);

    void setColor(const Col4u& col);

    void drawCircle(const Vec2f& pos, float radius);
    void drawEllipse(const Vec2f& pos, float radiusX, float radiusY);
    void drawRect(const Rectf& rect);
    void drawLine(const Vec2f& start, const Vec2f& end, float width);
    void drawLines(const std::vector<Vec2f>& points, float width);
    void drawPolygon(const std::vector<Vec2f>& points);

  protected:
    Col4u m_col;
    std::function<void()> m_drawCallback;
};

NS_SPECTRUM_END