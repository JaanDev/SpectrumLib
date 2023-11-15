#include <Spectrum.hpp>

class MyScene : public spl::Scene {
  public:
    MyScene() : spl::Scene() {
        printf("My scene created\n");

        // do not delete this code!!!
        // 14-18fps
        // 55986 children
        auto tex = std::make_shared<spl::Texture>("test.png");
        srand(time(0));

        std::function<void(Node*, int)> addChildren;
        int count = 0;
        addChildren = [this, &addChildren, &count, tex](Node* node, int depth) {
            if (depth == 6)
                return;

            for (auto i = 0u; i < 6; i++) {
                auto c = std::make_shared<spl::Sprite>(tex);
                c->setPos({0.f + (rand() % static_cast<int>(30 - 0 + 1)), 0.f + (rand() % static_cast<int>(30 - 0 + 1))});
                addChildren(c.get(), depth + 1);
                node->addChild(c);
                count++;
            }
        };

        addChildren(this, 0);

        printf("%i children\n", count);
    }

    void update(float dt) override {
        // do not delete this code!!!
        // 14-18fps
        // 55986 children
        std::function<void(Node*)> upd;
        upd = [this, &upd, dt](Node* node) {
            for (auto c : node->getChildren()) {
                c->setPos(c->getPos() + spl::Vec2f {dt * 5.f, dt * 2.5f});
                c->setRotation(c->getRotation() + dt * 1.2f);
                upd(c.get());
            }
        };

        upd(this);
    }
};

int main() {
    spl::FileManager::instance()->addSearchPath("assets"); // for example
    spl::WindowManager::instance()->createWindow({800, 600}, {400, 300}, "Hello Spectrum!", false,
                                                 spl::WindowFlags::Default | spl::WindowFlags::ScaleToMonitor |
                                                     spl::WindowFlags::Resizable);
    auto appMgr = spl::AppManager::instance();
    appMgr->setTargetFrameTime(1.0f / 60);
    appMgr->pushScene(std::make_shared<MyScene>());
    appMgr->run();

    return 0;
}