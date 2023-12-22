#include <Spectrum.hpp>

#include <utf8.h>
#include <logger.hpp>

using namespace spl;
#define create std::make_shared

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColor({.1, .1, .1});

        auto fm = FontManager::instance();
        fm->loadFont("C:\\Windows\\Fonts\\Arial.ttf", "arial", 36,
                     {FontRange::BasicLatin, {0x401, 0x451}}); // only useful cyrillic letters
        fm->loadBitmapFont("pusab.fnt", "pusab");

        auto ttfSpr = create<Sprite>(fm->getFont("arial").fontAtlas);
        ttfSpr->setPos({0, 0});
        ttfSpr->setAnchorPoint({0, 0});
        ttfSpr->setScale(120.f / ttfSpr->getTexture()->getSize().w);
        addChild(ttfSpr);

        auto fntSpr = create<Sprite>(fm->getFont("pusab").fontAtlas);
        fntSpr->setPos({400, 0});
        fntSpr->setAnchorPoint({1, 0});
        fntSpr->setScale(120.f / fntSpr->getTexture()->getSize().w);
        addChild(fntSpr);

        auto transparentSpr = create<Sprite>("alphaSprite.png");
        addChild(transparentSpr, 999);
        transparentSpr->setPos({200, 200});

        std::string str = "Привет, SpectrumLib!";

        auto label = create<Label>(str, "arial");
        label->setPos({100, 100});
        label->setScale(0.5f);
        addChild(label);

        auto label2 = create<Label>(str, "arial");
        label2->setPos({100, 150});
        addChild(label2);
    }

  private:
    //
};

int main() {
    FileManager::instance()->addSearchPath("assets");
    WindowManager::instance()->createWindow({1024, 768}, {400, 300}, "Hello Spectrum!", false,
                                            WindowFlags::Default | WindowFlags::ScaleToMonitor | WindowFlags::Resizable);

    auto appMgr = AppManager::instance();
    appMgr->setTargetFrameTime(1.0f / 60);
    appMgr->pushScene(create<MyScene>());
    appMgr->run();

    return 0;
}