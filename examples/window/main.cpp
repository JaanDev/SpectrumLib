#include <Spectrum.hpp>

#include "logger.hpp"
#include "MiniFunction.hpp"

using namespace spl;
#define create std::make_shared
#define ptr std::shared_ptr

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        setBGColor({1.0f, 1.0f, 1.0f});

        int x = 10;

        MiniFunction<void(int, int)> fcn = [&x](int a, float b) -> void {
            logD("a {} b {:.2f} x {}", a, b, x);
        };

        fcn(10, 15);
        x = 47;
        fcn(1, 2);

        logD("{} vs {}", sizeof(MiniFunction<void(int, float)>), sizeof(std::function<void(int, float)>));

        WindowManager::get()->setOnCloseCallback([]() {
            logD("ON CLOSE");
            return true;
        });

        WindowManager::get()->setFilesDroppedCallback([](std::vector<std::string> files) {
            for (const auto& name : files) {
                logD("{}", name);
            }
        });
    }
};

int main() {
    FileManager::get()->addSearchPath("assets");
    WindowManager::get()->createWindow({800, 450}, {800, 450}, "Hello Spectrum!", false,
                                       WindowFlags::Default | WindowFlags::Resizable | WindowFlags::ScaleToMonitor);

    auto appMgr = AppManager::get();
    appMgr->setTargetFrameTime(1 / 60.0f);
    appMgr->pushScene(create<MyScene>());
    appMgr->run();

    return 0;
}