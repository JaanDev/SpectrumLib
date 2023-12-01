#include <Spectrum.hpp>

using namespace spl;
#define create std::make_shared

class MySprite : public Sprite {
  public:
    using Sprite::Sprite;

    virtual void onMouseEvent(MouseEventType evtType, const Vec2f& mousePos) override {
        if (evtType == MouseEventType::MouseEnterArea) {
            printf("Enter area\n");
            setColor({0, 255, 0});
        } else if (evtType == MouseEventType::MouseLeaveArea) {
            printf("Leave area\n");
            setColor({255, 255, 255});
        }
    }

    virtual void onKeyEvent(int key, int scancode, int action, int mods) override {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_LEFT) {
                setPosX(getPosX() - 10);
            } else if (key == GLFW_KEY_RIGHT) {
                setPosX(getPosX() + 10);
            }
        }
    };
};

class MyScene : public Scene {
  public:
    MyScene() : Scene() {
        printf("My scene created\n");

        InputDispatcher::instance()->registerMouseEvents(this);
        InputDispatcher::instance()->registerMouseScrollEvents(this);

        m_spr = create<MySprite>("test.png");
        m_spr->setPos(AppManager::instance()->getWinSize() / 2.f);
        addChild(m_spr);

        auto tm = TextureManager::instance();
        tm->loadSpriteSheet("assets/test.json");
        auto part1 = tm->getTextureFrame("part1.png");
        auto part2 = tm->getTextureFrame("part2.png");

        auto spr = create<Sprite>(part1);
        spr->setPos({100, 100});
        addChild(spr);

        // works fine
        spr->setTextureFrame(part2);

        auto fm = FontManager::instance();
        fm->loadFont("C:\\Windows\\Fonts\\Arial.ttf", "arial", 36);

        auto fontSpr = create<Sprite>(fm->getFont("arial").fontAtlas);
        fontSpr->setPos({200, 100});
        fontSpr->setAnchorPoint({0.5f, 0.0f});
        fontSpr->setScale(0.5f);
        addChild(fontSpr);

        std::string str = "spectrum!";

        auto font = fm->getFont("arial");
        int posX = 100;

        for(char c : str) {
            auto sprframe = std::make_shared<TextureFrame>(font.fontAtlas, font.glyphs[c].textureRect, false);
            printf("%d %d %d %d\n", sprframe->getRect().x, sprframe->getRect().y, sprframe->getRect().w, sprframe->getRect().h);
            auto ch = create<Sprite>(sprframe);
            ch->setPosX(posX + font.glyphs[c].xOffset);
            ch->setPosY(10);
            posX += font.glyphs[c].xAdvance;
            addChild(ch);
        }

        InputDispatcher::instance()->registerMouseEvents(m_spr.get());
        InputDispatcher::instance()->registerKeyEvents(m_spr.get());
    }

    virtual void onMouseBtn(int button, bool down, int mods) override {
        if (down) {
            if (button == GLFW_MOUSE_BUTTON_LEFT)
                m_spr->setScale(m_spr->getScaleX() + 0.1f);
            else if (button == GLFW_MOUSE_BUTTON_RIGHT)
                m_spr->setRotation(m_spr->getRotation() + 5.f);
            else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                m_spr->setScale(1.f);
                m_spr->setPos(AppManager::instance()->getWinSize() / 2.f);
                m_spr->setRotation(0.f);
            }
        }
    }

    virtual void onMouseScroll(const Vec2f& delta) override {
        //
        m_spr->setPos(m_spr->getPos() + delta * 8.f);
    };

    // void update(float dt) override {}

  private:
    std::shared_ptr<Sprite> m_spr;
};

int main() {
    FileManager::instance()->addSearchPath("assets");
    WindowManager::instance()->createWindow({800, 600}, {400, 300}, "Hello Spectrum!", false,
                                            WindowFlags::Default | WindowFlags::ScaleToMonitor | WindowFlags::Resizable);

    auto appMgr = AppManager::instance();
    appMgr->setTargetFrameTime(1.0f / 60);
    appMgr->pushScene(create<MyScene>());
    appMgr->run();

    return 0;
}