#include <Spectrum.hpp>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        auto am = AudioManager::get();
        am->preloadSampleFile(FileManager::get()->fullPathForFile("my-heart.mp3").string());
        am->playSample("my-heart.mp3", 1);
    }
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "Hello Spectrum! [audio]", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);
    FileManager::get()->addSearchPath("assets");

    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}