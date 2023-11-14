#include <Spectrum.hpp>

class MyScene : public spl::Scene {
  public:
    MyScene() : spl::Scene() { printf("My scene created\n"); }

    void update(float dt) override {
        printf("MyScene::update\n");
    }

    void draw() override {
        printf("MyScene::draw\n");
        glColor3f(0.f, 1.f, 0.f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.f, 0.f);
        glVertex2f(-0.5f, 0.f);
        glVertex2f(0.f, -0.5f);
        glEnd();
    }
};

int main() {
    // spl::FileManager::instance()->addSearchPath("assets"); // for example
    spl::WindowManager::instance()->createWindow({800, 600}, {300, 200}, "Hello Spectrum!", false,
                                                 spl::WindowFlags::Default | spl::WindowFlags::ScaleToMonitor);
    auto appMgr = spl::AppManager::instance();
    appMgr->setTargetFrameTime(1.0 / 60);
    appMgr->pushScene(std::make_shared<MyScene>());
    appMgr->run();

    return 0;
}