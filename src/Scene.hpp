#pragma once
#include "utils.hpp"
#include "Node.hpp"

NS_SPECTRUM_BEGIN

class SPL_API Scene : public Node {
  public:
    Scene();

    inline void setBGColor(const Col3f& color) { m_bgColor = color; }
    inline const Col3f& getBGColor() const { return m_bgColor; }

  private:
    Col3f m_bgColor;
};

NS_SPECTRUM_END