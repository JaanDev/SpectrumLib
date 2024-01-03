#pragma once
#include "utils.hpp"
#include "Node.hpp"

NS_SPECTRUM_BEGIN

class SPL_API Scene : public Node {
  public:
    Scene();

    inline void setBGColorF(const Col3f& color) { m_bgColor = color; }
    inline void setBGColorU(const Col3u& color) { m_bgColor = utils::IntToCol3f(utils::Col3uToInt(color)); } // :skull:
    inline const Col3f& getBGColor() const { return m_bgColor; }

  private:
    Col3f m_bgColor;
};

NS_SPECTRUM_END