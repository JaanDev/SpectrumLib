#pragma once
#include <vector>
#include "utils.hpp"
#include "Node.hpp"
#include "WindowManager.hpp"

NS_SPECTRUM_BEGIN

class InputDispatcher {
    friend class WindowManager;

  public:
    static InputDispatcher* instance();
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

  private:
    // всякие функции для WindowManager которые принимают данные и отправляют их в вектора нодов

    std::vector<Node*> m_mouseEvents;
    std::vector<Node*> m_mouseScrollEvents;
    std::vector<Node*> m_keyEvents;
    std::vector<Node*> m_textEvents;
};

NS_SPECTRUM_END