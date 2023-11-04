#include "ActionTintTo.hpp"

NS_SPECTRUM_BEGIN

ActionTintTo::ActionTintTo(EasingType easing, float duration, const Col3u& startCol, const Col3u& endCol)
    : Action(easing, duration), m_startCol(startCol), m_endCol(endCol) {}

void ActionTintTo::update(float dt) {
    Action::update(dt);

    auto spr = dynamic_cast<Sprite*>(m_node);

    if (spr)
        spr->setColor(utils::lerpValue(m_startCol, m_endCol, m_progress));
}

NS_SPECTRUM_END