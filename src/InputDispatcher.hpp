#pragma once
#include <vector>
#include "utils.hpp"
#include "Node.hpp"
#include "WindowManager.hpp"

NS_SPECTRUM_BEGIN

class InputDispatcher {
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

    void addPassiveMouseListener(std::function<void(MouseEventType evtType, const Vec2f& mousePos)> callback);
    void addPassiveMouseScrollListener(std::function<void(const Vec2f& delta)> callback);
    void addPassiveKeyListener(std::function<void(int key, int scancode, int action, int mods)> callback);
    void addPassiveTextListener(std::function<void(unsigned int codepoint)> callback);

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
    std::function<void(MouseEventType evtType, const Vec2f& mousePos)> m_mouseCb;
    std::function<void(const Vec2f& delta)> m_mouseScrollCb;
    std::function<void(int key, int scancode, int action, int mods)> m_keyCb;
    std::function<void(unsigned int codepoint)> m_textCb;
};

NS_SPECTRUM_END