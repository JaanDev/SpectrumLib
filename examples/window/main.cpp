#include <Spectrum.hpp>

class MyScene : public spl::Scene {
  public:
    MyScene() : spl::Scene() {
        printf("My scene created\n");
        auto spr = std::make_shared<spl::Sprite>(std::make_shared<spl::Texture>("test.png"));
        // spr->setPos({100, 100});
        addChild(spr);
    }
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