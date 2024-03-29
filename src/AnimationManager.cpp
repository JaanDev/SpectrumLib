#include "AnimationManager.hpp"

NS_SPECTRUM_BEGIN

AnimationManager* AnimationManager::get() {
    static auto instance = AnimationManager();
    return &instance;
}

AnimationManager::AnimationManager() : m_anims({}) {}

void AnimationManager::addAnim(std::shared_ptr<Animation> anim, const std::string& id) {
    m_anims[id] = anim;
}

void AnimationManager::removeAnim(const std::string& id) {
    if (auto it = m_anims.find(id); it != m_anims.end())
        m_anims.erase(it);
}

std::shared_ptr<Animation> AnimationManager::getAnim(const std::string& id) {
    return m_anims.count(id) > 0 ? m_anims[id] : nullptr;
}

NS_SPECTRUM_END
