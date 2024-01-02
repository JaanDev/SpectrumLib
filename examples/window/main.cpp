#include <Spectrum.hpp>

using namespace spl;
#define create std::make_shared

class MyScene : public Scene {
  public:
    MyScene() : Scene(), m_val(0.f) {
        printf("My scene created\n");

        setBGColor({1.0f, 1.0f, 1.0f});

        InputDispatcher::get()->registerKeyEvents(this);
    }

    virtual void onKeyEvent(int key, int scancode, int action, int mods) override {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_X) {
                auto spr = create<Sprite>("test.png");
                spr->setScale(0.5f);
                spr->setRotation(m_val);
                m_val += 5.f;
                spr->setPos(AppManager::get()->getWinSize() / 2.f);
                addChild(spr);
            } else if (key == GLFW_KEY_ESCAPE) {
                AppManager::get()->end();
            }
        }
    }

    virtual void update(float dt) override {
        for (auto child : m_children) {
            child->setPos(WindowManager::get()->getMousePos());
        }
    }

  private:
    float m_val;
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