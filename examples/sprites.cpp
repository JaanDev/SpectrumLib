#include <Spectrum.hpp>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColorU({181, 181, 181});

        auto spr = Sprite::createWithTexName("alphaSprite.png");
        spr->setPos({100, 100});
        addChild(spr);

        auto tex = std::make_shared<Texture>("test.png");
        auto spr2 = Sprite::create(tex);
        spr2->setPos({200, 100});
        spr2->setScale({.5f, 1.5f});
        spr2->setRotation(45);
        addChild(spr2);

        auto spr3 = Sprite::createWithTexName("test2.png");
        spr3->setAnchorPoint({0, 0});
        spr3->setRotation(30);
        spr2->addChild(spr3);
        spr3->setOpacity(0.5f);

        m_spr = spr;
    }

    void update(float dt) override {
        m_spr->setPos(WindowManager::get()->getMousePos());
        //
    }

  private:
    shared_ptr<Sprite> m_spr;
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "SpectrumLib example [sprites]", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);
    FileManager::get()->addSearchPath("assets");
    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}