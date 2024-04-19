#include <Spectrum.hpp>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColorU({255, 255, 255});

        auto spr = make_shared<Sprite>("alphaSprite.png");
        spr->setPos({100, 100});
        addChild(spr);

        auto spr2 = make_shared<Sprite>("test.png");
        spr2->setPos({200, 100});
        spr2->setScale({.5f, 1.5f});
        spr2->setRotation(45);
        addChild(spr2);

        auto spr3 = make_shared<Sprite>("test2.png");
        spr3->setAnchorPoint({0, 0});
        spr3->setRotation(30);
        spr2->addChild(spr3);
    }
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