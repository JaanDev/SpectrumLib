#include "AnimSprite.hpp"

#include "AnimationManager.hpp"

NS_SPECTRUM_BEGIN

AnimSprite::AnimSprite() : Sprite(std::shared_ptr<Texture>(nullptr)), m_curAnim(nullptr) {}

void AnimSprite::runAnim(const std::string& id) {
    m_curAnim = AnimationManager::get()->getAnim(id);
}

void AnimSprite::runAnim(std::shared_ptr<Animation> anim) {
    m_curAnim = anim;
}

void AnimSprite::update(float dt) {
    Node::update(dt);

    if (m_curAnim)
        m_curAnim->update(dt);
}

void AnimSprite::draw() {
    if (!m_curAnim)
        return;

    m_texture = m_curAnim->getTexture();
    Sprite::draw();
}

NS_SPECTRUM_END
