#include <Spectrum.hpp>

class MyScene : public spl::Scene {
  public:
    MyScene() : spl::Scene() {
        printf("My scene created\n");
        m_spr = std::make_shared<spl::Sprite>(std::make_shared<spl::Texture>("test.png"));
        m_spr->setPos(spl::AppManager::instance()->getWinSize() / 2.f);
        // m_spr->setAnchorPoint({0, 0});
        addChild(m_spr);
    }

    void update(float dt) override {
        // auto newPos = m_spr->getPos() + spl::Vec2f {dt * 25.f, dt * 25.f / 2.f};
        // m_spr->setPos(newPos);
        m_spr->setScale(m_spr->getScale() + spl::Vec2f {dt, dt} * 0.05f);
        // m_spr->setRotation(m_spr->getRotation() + dt * 1.2f);
    }

    private:
    std::shared_ptr<spl::Sprite> m_spr;
};

int main() {
    // spl::FileManager::instance()->addSearchPath("assets"); // for example
    spl::WindowManager::instance()->createWindow({800, 600}, {400, 300}, "Hello Spectrum!", false,
                                                 spl::WindowFlags::Default | spl::WindowFlags::ScaleToMonitor);
    auto appMgr = spl::AppManager::instance();
    appMgr->setTargetFrameTime(1.0 / 60);
    appMgr->pushScene(std::make_shared<MyScene>());
    appMgr->run();

    return 0;
}