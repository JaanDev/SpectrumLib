#include "ShapeNode.hpp"

NS_SPECTRUM_BEGIN

ShapeNode::ShapeNode() : m_col({255, 255, 255, 255}), m_drawCallback(nullptr) {}

void ShapeNode::draw() {}

void ShapeNode::setDrawCallback(std::function<void()> callback) {}

void ShapeNode::setColor(const Col4u& col) {}
void ShapeNode::drawCircle(const Vec2f& pos, float radius) {}
void ShapeNode::drawEllipse(const Vec2f& pos, float radiusX, float radiusY) {}
void ShapeNode::drawRect(const Rectf& rect) {}
void ShapeNode::drawLine(const Vec2f& start, const Vec2f& end, float width) {}
void ShapeNode::drawLines(const std::vector<Vec2f>& points, float width) {}
void ShapeNode::drawPolygon(const std::vector<Vec2f>& points) {}

NS_SPECTRUM_END