#include <Spectrum.hpp>

#include <utf8.h>
#include <logger.hpp>

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

        auto label = create<Label>("Привет, SpectrumLib!", "8bit");
        label->setColor({ 128, 128, 128 });
        label->setPos(AppManager::instance()->getWinSize() / 2);
        addChild(label);
    }

  private:
    //
};

int main() {
    FileManager::instance()->addSearchPath("assets");
    WindowManager::instance()->createWindow({800, 450}, {800, 450}, "Hello Spectrum!", false,
                                            WindowFlags::Default | WindowFlags::ScaleToMonitor | WindowFlags::Resizable);

    auto appMgr = AppManager::instance();
    appMgr->setTargetFrameTime(1.0f / 60);
    appMgr->pushScene(create<MyScene>());
    appMgr->run();

    return 0;
}