#include <Spectrum.hpp>

class MyScene : public spl::Scene {
  public:
    MyScene() : spl::Scene() {
        printf("My scene created\n");
        m_spr = std::make_shared<spl::Sprite>(std::make_shared<spl::Texture>("test.png"));
        m_spr->setPos((spl::Vec2f)spl::AppManager::instance()->getWinSize() / 2.f - spl::Vec2f {100, 50});
        // m_spr->setAnchorPoint({0.1, 0.1});
        m_spr->setScale(0.7f);
        addChild(m_spr);

        auto tex2 = std::make_shared<spl::Texture>("test2.png");
        tex2->setTexParams({.minFilter = GL_LINEAR_MIPMAP_LINEAR, .magFilter = GL_NEAREST, .wrapS = GL_CLAMP, .wrapT = GL_CLAMP});
        m_spr2 = std::make_shared<spl::Sprite>(tex2);
        m_spr2->setPos({0, 0});
        m_spr2->setAnchorPoint({0, 0});
        m_spr->addChild(m_spr2);
    }

    void update(float dt) override {
        auto newPos = m_spr->getPos() + spl::Vec2f {dt * 10.f, dt * 10.f / 2.f};
        m_spr->setPos(newPos);
        m_spr->setScale(m_spr->getScale() + spl::Vec2f {dt, dt} * 0.05f);
        m_spr2->setScale(m_spr2->getScale() + spl::Vec2f {dt, dt} * 0.1f);
        m_spr->setRotation(m_spr->getRotation() + dt * 12.f);
        m_spr2->setRotation(m_spr2->getRotation() + dt * 18.f);

        this->setBGColor({this->getBGColor().r + dt * 0.1f, 0, 0});
    }

  private:
    std::shared_ptr<spl::Sprite> m_spr;
    std::shared_ptr<spl::Sprite> m_spr2;
};

int main() {
    spl::FileManager::instance()->addSearchPath("assets"); // for example
    spl::WindowManager::instance()->createWindow({800, 600}, {400, 300}, "Hello Spectrum!", false,
                                                 spl::WindowFlags::Default | spl::WindowFlags::ScaleToMonitor |
                                                     spl::WindowFlags::Resizable);
    auto appMgr = spl::AppManager::instance();
    appMgr->setTargetFrameTime(1.0f / 60);
    appMgr->pushScene(std::make_shared<MyScene>());
    appMgr->run();

    return 0;
}