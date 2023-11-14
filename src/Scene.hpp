#pragma once
#include "utils.hpp"
#include "Node.hpp"

NS_SPECTRUM_BEGIN

class Scene : public Node {
  public:
    Scene();

    void setColor(Col3f color);
    Col3f getColor();

  private:
    Col3f m_color;
};

NS_SPECTRUM_END