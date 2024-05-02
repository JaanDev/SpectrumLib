#include <Spectrum.hpp>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColorU({120, 220, 240});

        FontManager::get()->loadFont("DiaryOfAn8BitMage-lYDD.ttf", "testfont", 32, {FontRange::BasicLatin, FontRange::Cyrillic});
        FontManager::get()->loadFont("XiaoXinChaoKu.ttf", "testfont2", 48,
                                     {FontRange::BasicLatin, FontRange::Cyrillic, FontRange::CjkUnifiedIdeographs, {0x3002, 0x3002}}); // 0x3002 is 。
        FontManager::get()->loadBitmapFont("pusab.fnt", "bitmap-font");

        auto label1 = make_shared<Label>("Hello Spectrum!", "testfont");
        label1->setColor({30, 30, 30});
        label1->setPos({AppManager::get()->getWinSize().w / 2.f, 40});
        addChild(label1);

        auto label2 = make_shared<Label>("Very very 111 very very very long text", "testfont", spl::TextAlignment::Center, 100.f);
        label2->setColor({30, 30, 30});
        label2->setPos({AppManager::get()->getWinSize().w / 2.f, 60});
        label2->setAnchorPoint({0.5f, 0.f});
        addChild(label2);
        label2->setOpacity(0.5f);

        auto label3 = make_shared<Label>("Привет мир!", "testfont");
        label3->setColor({30, 30, 30});
        label3->setPos({AppManager::get()->getWinSize().w / 2.f, 150});
        addChild(label3);

        auto label4 = make_shared<Label>("Привет мир! 这可能是你的广告。", "testfont2");
        label4->setColor({30, 30, 30});
        label4->setPos({AppManager::get()->getWinSize().w / 2.f, 160});
        label4->setAnchorPoint({0.5f, 0.f});
        addChild(label4);

        auto label5 = make_shared<Label>("Hello bitmap font!", "bitmap-font", spl::TextAlignment::Right);
        label5->setPos(AppManager::get()->getWinSize().toVec());
        label5->setAnchorPoint({1.0f, 1.0f});
        label5->setScale(.4f);
        addChild(label5);
    }
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "SpectrumLib example [font]", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);
    FileManager::get()->addSearchPath("assets");
    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}