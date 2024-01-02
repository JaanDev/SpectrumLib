#include "Joystick.hpp"

NS_SPECTRUM_BEGIN

Joystick::Joystick(int id) : m_id(id) {}

Joystick::Joystick() : Joystick(0) {}

bool Joystick::isPresent() {
    return glfwJoystickPresent(m_id);
}

std::string Joystick::getName() {
    auto name = glfwGetJoystickName(m_id);
    return name == nullptr ? "" : name;
}

std::string Joystick::getGUID() {
    auto guid = glfwGetJoystickGUID(m_id);
    return guid == nullptr ? "" : guid;
}

bool Joystick::isGamepad() {
    return glfwJoystickIsGamepad(m_id);
}

NS_SPECTRUM_END