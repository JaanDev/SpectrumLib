#pragma once
#include "utils.hpp"
#include "Node.hpp"
#include "Texture.hpp"

NS_SPECTRUM_BEGIN

class ShapeNodeEx : public Node {
  public:
    ShapeNodeEx();
  
    virtual void draw() override;

    void setShape(ShapeType shape);
    void setFill(FillType fill);

    void setLineColor(Col4u color);
    void setLineWidth(float width);

    void setGradientStartCol(Col4u color);
    void setGradientEndCol(Col4u color);
    // all is from 0 to 1
    void setGradientPositions(Vec2f start, Vec2f end);

    void setTexture(std::shared_ptr<Texture> texture);

    void setPolygonPoints(std::vector<Vec2f> points);

    // for circle x = y
    void setEllipseRadius(float x, float y);

  protected:
    ShapeType m_shapeType;
    FillType m_fillType;

    Vec2f m_ellipseRadius;

    std::shared_ptr<Texture> m_texture;

    float m_lineWidth;
    Col4u m_lineCol;

    Col4u m_gradientStartCol;
    Col4u m_gradientEndCol;
    Vec2f m_gradientStartPos;
    Vec2f m_gradientEndPos;

    std::vector<Vec2f> m_polygonPoints;
};

NS_SPECTRUM_END