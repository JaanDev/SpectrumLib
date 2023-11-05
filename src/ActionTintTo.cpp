#include "ActionTintTo.hpp"

#include "Sprite.hpp"

NS_SPECTRUM_BEGIN

ActionTintTo::ActionTintTo(EasingType easing, float duration, int repeat, const Col3u& startCol, const Col3u& endCol)
    : Action(easing, duration, repeat), m_startCol(startCol), m_endCol(endCol) {}

void ActionTintTo::update(float dt) {
    Action::update(dt);

    auto spr = dynamic_cast<Sprite*>(m_node);

    if (spr)
        spr->setColor(utils::lerpValue(m_startCol, m_endCol, m_progress));
}

void ActionTintTo::setNode(Node* node) {
    auto spr = dynamic_cast<Sprite*>(node);
    if (spr) {
        Action::setNode(node);
        spr->setColor(utils::lerpValue(m_startCol, m_endCol, m_progress));
    }
}

NS_SPECTRUM_END