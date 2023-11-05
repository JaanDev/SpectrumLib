#pragma once
#include "utils.hpp"
#include "types.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"

NS_SPECTRUM_BEGIN

class AnimSprite : public Sprite {
  public:
    AnimSprite();

    void runAnim(const std::string& id);
    void runAnim(std::shared_ptr<Animation> anim);

    virtual void update(float dt) override;
    virtual void draw() override;

  protected:
    std::shared_ptr<Animation> m_curAnim;
};

NS_SPECTRUM_END