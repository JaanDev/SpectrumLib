#include <Spectrum.hpp>

using namespace spl;
#define create std::make_shared

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColor({1.0f, 1.0f, 1.0f});

        auto fm = FontManager::instance();
        fm->loadFont("DiaryOfAn8BitMage-lYDD.ttf", "8bit", 30,
                     {FontRange::BasicLatin, {0x401, 0x451}}); // only useful cyrillic letters
        fm->loadBitmapFont("pusab.fnt", "pusab");

        auto label2 = create<Label>("Привет, SpectrumLib!", "pusab");
        label2->setColor({ 128, 128, 128 });
        label2->setAnchorPoint({0, 0});
        label2->setScale(0.3f);
        addChild(label2);
    }
};

int main() {
    FileManager::instance()->addSearchPath("assets");
    WindowManager::instance()->createWindow({800, 450}, {800, 450}, "Hello Spectrum!", false,
                                            WindowFlags::Default | WindowFlags::ScaleToMonitor | WindowFlags::Resizable);

    auto appMgr = AppManager::instance();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(create<MyScene>());
    appMgr->run();

    return 0;
}