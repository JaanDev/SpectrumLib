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
                                     {FontRange::BasicLatin, FontRange::Cyrillic, FontRange::CjkUnifiedIdeographs});

        auto label1 = make_shared<Label>("Hello Spectrum!", "testfont");
        label1->setColor({30, 30, 30});
        label1->setPos({AppManager::get()->getWinSize().w / 2.f, 60});
        addChild(label1);

        auto label2 = make_shared<Label>("Very very 111 very very very long text", "testfont", spl::TextAlignment::Center, 100.f);
        label2->setColor({30, 30, 30});
        label2->setPos({AppManager::get()->getWinSize().w / 2.f, 80});
        label2->setAnchorPoint({0.5f, 0.f});
        addChild(label2);

        auto label3 = make_shared<Label>("Привет мир!", "testfont");
        label3->setColor({30, 30, 30});
        label3->setPos({AppManager::get()->getWinSize().w / 2.f, 170});
        addChild(label3);

        auto label4 = make_shared<Label>("Привет мир! 你好中国!", "testfont2");
        label4->setColor({30, 30, 30});
        label4->setPos({AppManager::get()->getWinSize().w / 2.f, 180});
        label4->setAnchorPoint({0.5f, 0.f});
        addChild(label4);
    }
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "Hello Spectrum! [font]", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);
    FileManager::get()->addSearchPath("assets");
    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}