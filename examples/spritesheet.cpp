#include <Spectrum.hpp>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColorU({240, 240, 240});

        TextureManager::get()->loadSpriteSheet("spritesheet.json");

        auto s1 = make_shared<Sprite>(TextureManager::get()->getTextureFrame("image 1.png"));
        s1->setPos({10, 10});
        s1->setAnchorPoint({0, 0});
        addChild(s1);

        auto s2 = make_shared<Sprite>(TextureManager::get()->getTextureFrame("mem.png"));
        s2->setPos({390, 290});
        s2->setAnchorPoint({1, 1});
        addChild(s2);

        auto s3 = make_shared<Sprite>(TextureManager::get()->getTextureFrame("opengl.png"));
        s3->setPos({390, 10});
        s3->setAnchorPoint({1, 0});
        addChild(s3);

        auto s4 = make_shared<Sprite>(TextureManager::get()->getTextureFrame("pixelart.png"));
        s4->setPos({10, 290});
        s4->setAnchorPoint({0, 1});
        s4->setScale(10);
        s4->getTextureFrame()->getTexture()->setTexParams({.magFilter = GL_NEAREST});
        addChild(s4);
    }
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "Hello Spectrum! [spritesheet]", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);
    FileManager::get()->addSearchPath("assets");
    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}