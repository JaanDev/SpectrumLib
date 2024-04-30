#include "AnimSprite.hpp"

#include "AnimationManager.hpp"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

AnimSprite::AnimSprite() : Sprite(), m_curAnim(nullptr) {}

void AnimSprite::runAnim(const std::string& id) {
    m_curAnim = AnimationManager::get()->getAnim(id);
}

void AnimSprite::runAnim(std::shared_ptr<Animation> anim) {
    m_curAnim = anim;
    setTextureFrame(anim->getFrame());
}

void AnimSprite::update(float dt) {
    Node::update(dt);

    if (m_curAnim)
        m_curAnim->update(dt);
}

void AnimSprite::draw() {
    if (!m_curAnim)
        return;

    if (m_curAnim->isNewFrame()) {
        setTextureFrame(m_curAnim->getFrame());
    }

    Sprite::draw();
}

NS_SPECTRUM_END
