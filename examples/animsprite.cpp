#include <Spectrum.hpp>

#include <format>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColorU({255, 255, 255});
        
        auto spr = make_shared<AnimSprite>();

        TextureManager::get()->loadSpriteSheet("animSpriteSheet.json");

        auto animIdleFront = Animation::createWithFrameNames(1 / 15.0f, -1, "Idle_Front{}.png", 1, 6);

        spr->runAnim(animIdleFront);
        spr->setScale(10.f);
        spr->setPos((AppManager::get()->getWinSize() / 2.f).toVec());

        addChild(spr);

        printf("ok\n");
    }
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "SpectrumLib example [animsprite]", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);
    FileManager::get()->addSearchPath("assets");
    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}