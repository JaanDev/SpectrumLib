#include <Spectrum.hpp>

class MyScene : public spl::Scene {
  public:
    MyScene() : spl::Scene() {
        printf("My scene created\n");
        m_spr = std::make_shared<spl::Sprite>(std::make_shared<spl::Texture>("test.png"));
        m_spr->setPos((spl::Vec2f)spl::AppManager::instance()->getWinSize() / 2.f - spl::Vec2f {100, 50});
        // m_spr->setAnchorPoint({0.5, 0.5});
        m_spr->setScale(0.7f);
        addChild(m_spr);

        m_spr2 = std::make_shared<spl::Sprite>(std::make_shared<spl::Texture>("test2.png"));
        m_spr2->setPos({0, 0});
        m_spr2->setAnchorPoint({0, 0});
        m_spr->addChild(m_spr2);
    }

    void update(float dt) override {
        auto newPos = m_spr->getPos() + spl::Vec2f {dt * 15.f, dt * 15.f / 2.f};
        m_spr->setPos(newPos);
        m_spr->setScale(m_spr->getScale() + spl::Vec2f {dt, dt} * 0.05f);
        m_spr2->setScale(m_spr2->getScale() + spl::Vec2f {dt, dt} * 0.1f);
        m_spr->setRotation(m_spr->getRotation() + dt * 0.5f);
        m_spr2->setRotation(m_spr2->getRotation() + dt * 0.5f);
    }

  private:
    std::shared_ptr<spl::Sprite> m_spr;
    std::shared_ptr<spl::Sprite> m_spr2;
};

int main() {
    spl::FileManager::instance()->addSearchPath("assets"); // for example
    spl::WindowManager::instance()->createWindow({800, 600}, {400, 300}, "Hello Spectrum!", false,
                                                 spl::WindowFlags::Default | spl::WindowFlags::ScaleToMonitor);
    auto appMgr = spl::AppManager::instance();
    appMgr->setTargetFrameTime(1.0f / 60);
    appMgr->pushScene(std::make_shared<MyScene>());
    appMgr->run();

    return 0;
}