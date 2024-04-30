#include <Spectrum.hpp>

#include <array>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColorU({255, 255, 255});

        TextureManager::get()->loadSpriteSheet("animSpriteSheet.json");

        std::array<const char*, 4> animNames = {"Idle_Front{}.png", "Idle_Left{}.png", "Idle_Back{}.png",
                                                "Idle_Rigth{}.png"}; // yes, its spelled 'rigth' in the sheet for some reason
        std::array<Vec2f, 4> sprPos = {Vec2f {200, 200}, Vec2f {100, 150}, Vec2f {200, 100}, Vec2f {300, 150}};

        for (auto i = 0; i < 4; i++) {
            auto anim = Animation::createWithFrameNames(1.0f / 5.0f, -1, animNames[i], 1, 6); // 5 fps
            anim->getTexture()->setTexParams({.magFilter = GL_NEAREST});

            auto spr = make_shared<AnimSprite>();
            spr->runAnim(anim);
            spr->setScale(5.0f);
            spr->setPos(sprPos[i]);

            addChild(spr);
        }
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