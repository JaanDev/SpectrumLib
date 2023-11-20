#include "InputDispatcher.hpp"

#include "logger.hpp"

NS_SPECTRUM_BEGIN

InputDispatcher* InputDispatcher::instance() {
    static auto instance = std::make_unique<InputDispatcher>();
    return instance.get();
}

InputDispatcher::InputDispatcher()
    : m_mouseEvents({}), m_mouseScrollEvents({}), m_keyEvents({}), m_textEvents({}), m_mouseCb(nullptr), m_mouseScrollCb(nullptr),
      m_keyCb(nullptr), m_textCb(nullptr) {}

void InputDispatcher::registerMouseEvents(Node* node) {
    if (std::find(m_mouseEvents.begin(), m_mouseEvents.end(), node) == m_mouseEvents.end())
        m_mouseEvents.push_back(node);
}

void InputDispatcher::registerMouseScrollEvents(Node* node) {
    if (std::find(m_mouseScrollEvents.begin(), m_mouseScrollEvents.end(), node) == m_mouseScrollEvents.end())
        m_mouseScrollEvents.push_back(node);
}

void InputDispatcher::registerKeyEvents(Node* node) {
    if (std::find(m_keyEvents.begin(), m_keyEvents.end(), node) == m_keyEvents.end())
        m_keyEvents.push_back(node);
}

void InputDispatcher::registerTextEvents(Node* node) {
    if (std::find(m_textEvents.begin(), m_textEvents.end(), node) == m_textEvents.end())
        m_textEvents.push_back(node);
}

void InputDispatcher::unregisterMouseEvents(Node* node) {
    if (auto it = std::find(m_mouseEvents.begin(), m_mouseEvents.end(), node); it != m_mouseEvents.end())
        m_mouseEvents.erase(it);
}

void InputDispatcher::unregisterMouseScrollEvents(Node* node) {
    if (auto it = std::find(m_mouseScrollEvents.begin(), m_mouseScrollEvents.end(), node); it != m_mouseScrollEvents.end())
        m_mouseScrollEvents.erase(it);
}

void InputDispatcher::unregisterKeyEvents(Node* node) {
    if (auto it = std::find(m_keyEvents.begin(), m_keyEvents.end(), node); it != m_keyEvents.end())
        m_keyEvents.erase(it);
}

void InputDispatcher::unregisterTextEvents(Node* node) {
    if (auto it = std::find(m_textEvents.begin(), m_textEvents.end(), node); it != m_textEvents.end())
        m_textEvents.erase(it);
}

void InputDispatcher::unregisterAllMouseEvents() {
    m_mouseEvents.clear();
}

void InputDispatcher::unregisterAllMouseScrollEvents() {
    m_mouseScrollEvents.clear();
}

void InputDispatcher::unregisterAllKeyEvents() {
    m_keyEvents.clear();
}

void InputDispatcher::unregisterAllTextEvents() {
    m_textEvents.clear();
}

void InputDispatcher::addPassiveMouseListener(std::function<void(MouseEventType evtType, const Vec2f& mousePos)> callback) {
    m_mouseCb = callback;
}

void InputDispatcher::addPassiveMouseScrollListener(std::function<void(const Vec2f& delta)> callback) {
    m_mouseScrollCb = callback;
}

void InputDispatcher::addPassiveKeyListener(std::function<void(int key, int scancode, int action, int mods)> callback) {
    m_keyCb = callback;
}

void InputDispatcher::addPassiveTextListener(std::function<void(unsigned int codepoint)> callback) {
    m_textCb = callback;
}

void InputDispatcher::keyCallback(int key, int scancode, int action, int mods) {
    for (auto node : m_keyEvents) {
        node->onKeyEvent(key, scancode, action, mods);
    }
}

void InputDispatcher::charCallback(unsigned int codepoint) {
    for (auto node : m_textEvents) {
        node->onTextEvent(codepoint);
    }
}

void InputDispatcher::mouseScrollCallback(const Vec2f& delta) {
    for (auto node : m_mouseScrollEvents) {
        node->onMouseScroll(delta);
    }
}

void InputDispatcher::mousePosCallback(const Vec2f& pos) {
    for (auto node : m_mouseEvents) {
        auto nodeRect = node->getRect();
        if (nodeRect.contains(pos)) {
            if (!node->isMouseOver()) {
                node->setMouseOver(true);
                node->onMouseEvent(MouseEventType::MouseEnterArea, pos);
            }

            node->onMouseEvent(MouseEventType::MouseMove, pos);
        } else {
            if (node->isMouseOver()) {
                node->setMouseOver(false);
                node->onMouseEvent(MouseEventType::MouseLeaveArea, pos);
            }
        }
    }
}

void InputDispatcher::mouseBtnCallback(int button, int action, int mods) {
    auto mousePos = WindowManager::instance()->getMousePos();
    
    for (auto node : m_mouseEvents) {
        auto nodeRect = node->getRect();
        if (nodeRect.contains(mousePos)) {
            node->onMouseBtn(button, action == GLFW_PRESS, mods);
        }
    }
}

NS_SPECTRUM_END
