#include <Spectrum.hpp>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColorU({255, 255, 255});

        auto spr = make_shared<Sprite>("assets/alphaSprite.png");
        spr->setPos({100, 100});
        addChild(spr);
    }
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "Hello Spectrum!", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);

    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}