#include <Spectrum.hpp>

int main() {
    // spl::FileManager::instance()->addSearchPath("assets"); // for example
    spl::WindowManager::instance()->createWindow({800, 600}, {300, 200}, "Hello Spectrum!", false, spl::WindowFlags::Default);
    auto appMgr = spl::AppManager::instance();
    // appMgr->pushScene(std::make_shared<MyScene>());
    appMgr->run();

    return 0;
}