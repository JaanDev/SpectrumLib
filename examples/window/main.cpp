#include <Spectrum.hpp>

#include "logger.hpp"

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
            switch (key) {
            case GLFW_KEY_R: {
                logD("hello world");
                auto& joystick = InputDispatcher::get()->getJoystick(0);
                logD("present {}", joystick.isPresent());
                logD("is gamepad {}", joystick.isGamepad());
                if (joystick.isPresent()) {
                    auto jname = joystick.getName();
                    logD("name {}", jname);
                    auto jguid = joystick.getGUID();
                    logD("GUID {}", jguid);
                    // auto mapping = 
                }
                if (joystick.isGamepad()) {
                    logD("!!!IS GAMEPAD IS GAMEPAD IS GAMEPAD IS GAMEPAD IS GAMEPAD IS GAMEPAD IS GAMEPAD IS GAMEPAD!!!");
                }

                int count;
                const float* axes = glfwGetJoystickAxes(0, &count);
                logD("count {}", count);
                for (auto i = 0u; i < count; i++) {
                    logD("{}", axes[i]);
                }

                // int count;
                const unsigned char* buttons = glfwGetJoystickButtons(0, &count);
                logD("count {}", count);
                for (auto i = 0u; i < count; i++) {
                    logD("{}", buttons[i]);
                }
            } break;
            default:
                break;
            }
        }
    }

    virtual void update(float dt) override {
        //
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