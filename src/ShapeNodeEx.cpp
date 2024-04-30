#include "ShapeNodeEx.hpp"

NS_SPECTRUM_BEGIN

ShapeNodeEx::ShapeNodeEx()
    : m_shapeType(spl::ShapeType::None), m_fillType(spl::FillType::None), m_ellipseRadius({0.f, 0.f}), m_texture(nullptr), m_lineWidth(1.f), m_lineCol({255, 255, 255, 255}),
      m_gradientStartCol({255, 255, 255, 255}), m_gradientEndCol({255, 255, 255, 255}), m_gradientStartPos({0.f, 0.f}), m_gradientEndPos({1.f, 1.f}), m_polygonPoints({}) {}

void ShapeNodeEx::draw() {}

void ShapeNodeEx::setShape(ShapeType shape) {}

void ShapeNodeEx::setFill(FillType fill) {}

void ShapeNodeEx::setLineColor(Col4u color) {}

void ShapeNodeEx::setLineWidth(float width) {}

void ShapeNodeEx::setGradientStartCol(Col4u color) {}

void ShapeNodeEx::setGradientEndCol(Col4u color) {}

void ShapeNodeEx::setGradientPositions(Vec2f start, Vec2f end) {}

void ShapeNodeEx::setTexture(std::shared_ptr<Texture> texture) {}

void ShapeNodeEx::setPolygonPoints(std::vector<Vec2f> points) {}

void ShapeNodeEx::setEllipseRadius(float x, float y) {}

NS_SPECTRUM_END