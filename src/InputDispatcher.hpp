#pragma once
#include <vector>
#include <array>
#include "utils.hpp"
#include "Node.hpp"
#include "WindowManager.hpp"
#include "Joystick.hpp"

NS_SPECTRUM_BEGIN

class SPL_API InputDispatcher {
    friend class WindowManager;

  public:
    static InputDispatcher* get();
    InputDispatcher();

    void registerMouseEvents(Node* node);
    void registerMouseScrollEvents(Node* node);
    void registerKeyEvents(Node* node);
    void registerTextEvents(Node* node);

    void unregisterMouseEvents(Node* node);
    void unregisterMouseScrollEvents(Node* node);
    void unregisterKeyEvents(Node* node);
    void unregisterTextEvents(Node* node);

    void unregisterAllMouseEvents();
    void unregisterAllMouseScrollEvents();
    void unregisterAllKeyEvents();
    void unregisterAllTextEvents();

    void addPassiveMouseListener(MiniFunction<void(MouseEventType evtType, const Vec2f& mousePos)> callback);
    void addPassiveMouseScrollListener(MiniFunction<void(const Vec2f& delta)> callback);
    void addPassiveKeyListener(MiniFunction<void(int key, int scancode, int action, int mods)> callback);
    void addPassiveTextListener(MiniFunction<void(unsigned int codepoint)> callback);

    Joystick& getJoystick(int id);

  private:
    void keyCallback(int key, int scancode, int action, int mods);
    void charCallback(unsigned int codepoint);
    void mouseScrollCallback(const Vec2f& delta);
    void mousePosCallback(const Vec2f& pos);
    void mouseBtnCallback(int button, int action, int mods);

    std::vector<Node*> m_mouseEvents;
    std::vector<Node*> m_mouseScrollEvents;
    std::vector<Node*> m_keyEvents;
    std::vector<Node*> m_textEvents;
    MiniFunction<void(MouseEventType evtType, const Vec2f& mousePos)> m_mouseCb;
    MiniFunction<void(const Vec2f& delta)> m_mouseScrollCb;
    MiniFunction<void(int key, int scancode, int action, int mods)> m_keyCb;
    MiniFunction<void(unsigned int codepoint)> m_textCb;
    std::array<Joystick, GLFW_JOYSTICK_LAST + 1> m_joysticks;
};

NS_SPECTRUM_END