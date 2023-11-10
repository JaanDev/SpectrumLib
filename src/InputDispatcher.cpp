#include "InputDispatcher.hpp"

NS_SPECTRUM_BEGIN

InputDispatcher* InputDispatcher::instance() {
    static auto instance = std::make_unique<InputDispatcher>();
    return instance.get();
}

InputDispatcher::InputDispatcher() : m_mouseEvents({}), m_mouseScrollEvents({}), m_keyEvents({}), m_textEvents({}) {}

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

NS_SPECTRUM_END
