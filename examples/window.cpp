#include <Spectrum.hpp>

using namespace spl;
using std::make_shared, std::shared_ptr;

class MyScene : public Scene {
  public:
    MyScene() : Scene() { printf("My scene created\n"); }
};

int main() {
    WindowManager::get()->createWindow({800, 600}, {400, 300}, "SpectrumLib example [window]", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);

    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(make_shared<MyScene>());
    appMgr->run();

    return 0;
}