#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "utils.hpp"
#include "types.hpp"
#include "Animation.hpp"

NS_SPECTRUM_BEGIN

class AnimationManager {
  public:
    static AnimationManager* instance();
    AnimationManager();

    void addAnim(std::shared_ptr<Animation> anim, const std::string& id);
    void removeAnim(const std::string& id);

    std::shared_ptr<Animation> getAnim(const std::string& id);

  private:
    std::unordered_map<std::string, std::shared_ptr<Animation>> m_anims;
};

NS_SPECTRUM_END