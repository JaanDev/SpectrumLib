#include <Spectrum.hpp>

#include <utf8.h>

using namespace spl;
#define create std::make_shared

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColor({.1, .1, .1});

        auto fm = FontManager::instance();
        fm->loadFont("C:\\Windows\\Fonts\\Arial.ttf", "arial", 36, {FontRange::BasicLatin, FontRange::Cyrillic});
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

        std::string str = "Привет, SpectrumLib!";

        float posY = 150.f;
        for (const std::string& fontName : {"arial", "pusab"}) {
            auto font = fm->getFont(fontName);
            int posX = 0;

            auto container = create<Node>();

            auto it = str.begin();
            auto end = str.end();
            while (it != str.end()) {
                auto cp = utf8::next(it, end);
                if (!font.glyphs.contains(cp))
                    continue;
                const auto& glyph = font.glyphs[cp];
                auto sprframe = std::make_shared<TextureFrame>(font.fontAtlas, glyph.textureRect, false);
                auto ch = create<Sprite>(sprframe);
                ch->setPosX(posX + glyph.xOffset);
                ch->setPosY(glyph.yOffset);
                ch->setAnchorPoint({0, 0});
                posX += glyph.xAdvance;
                container->addChild(ch);
            }

            container->setPos({20, posY});
            addChild(container);

            posY += 30;
        }

        getChildByIndex(3)->setScale(.4f); // pusab
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