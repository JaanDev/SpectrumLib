#include <Spectrum.hpp>

using namespace spl;

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        ///////////////////////////////////////
        // do not delete this code!!!
        // 14-18fps
        // 55986 children
        // auto tex = std::make_shared<Texture>("test.png");
        // srand(time(0));

        // std::function<void(Node*, int)> addChildren;
        // int count = 0;
        // addChildren = [this, &addChildren, &count, tex](Node* node, int depth) {
        //     if (depth == 6)
        //         return;

        //     for (auto i = 0u; i < 6; i++) {
        //         auto c = std::make_shared<Sprite>(tex);
        //         c->setPos({0.f + (rand() % static_cast<int>(30 - 0 + 1)), 0.f + (rand() % static_cast<int>(30 - 0 + 1))});
        //         addChildren(c.get(), depth + 1);
        //         node->addChild(c);
        //         count++;
        //     }
        // };

        // addChildren(this, 0);

        // printf("%i children\n", count);
        ///////////////////////////////////////

        auto spr = std::make_shared<Sprite>("test.png");
        spr->setPos(AppManager::instance()->getWinSize() / 2.f);
        // spr->setScale(2);
        // spr->setAnchorPoint({0, 1});
        addChild(spr);

        auto spr2 = std::make_shared<Sprite>("test2.png");
        spr2->setPos({200, 0});
        spr2->setScale(2.f);
        spr->addChild(spr2);

        setBGColor({.2f, .2f, .2f});
    }

    void update(float dt) override {
        /////////////////////////////////
        // do not delete this code!!!
        // 14-18fps
        // 55986 children
        // std::function<void(Node*)> upd;
        // upd = [this, &upd, dt](Node* node) {
        //     for (auto c : node->getChildren()) {
        //         c->setPos(c->getPos() + Vec2f {dt * 5.f, dt * 2.5f});
        //         c->setRotation(c->getRotation() + dt * 1.2f);
        //         upd(c.get());
        //     }
        // };

        // upd(this);
        /////////////////////////////////

        auto s = m_children[0];
        s->setPos(WindowManager::instance()->getMousePos());
        s->setRotation(s->getRotation() + dt * 150.f);
        s->setScale((sinf(AppManager::instance()->getTime() * 7.f) / 2.f + .5f) * 0.1f + 0.5f);
        auto colval = (unsigned char)((sinf(AppManager::instance()->getTime() * 2.f) / 2.f + .5f) * 255.f);
        ((Sprite*)s.get())->setColor({(unsigned char)(colval / 2), 0, colval});

        auto s2 = s->getChildren()[0];
        s2->setRotation(s2->getRotation() + dt * 100.f);
    }
};

int main() {
    FileManager::instance()->addSearchPath("assets");
    WindowManager::instance()->createWindow({800, 600}, {400, 300}, "Hello Spectrum!", false,
                                            WindowFlags::Default | WindowFlags::ScaleToMonitor | WindowFlags::Resizable);
    auto appMgr = AppManager::instance();
    appMgr->setTargetFrameTime(1.0f / 60);
    appMgr->pushScene(std::make_shared<MyScene>());
    appMgr->run();

    return 0;
}