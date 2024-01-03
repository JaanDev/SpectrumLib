#pragma once
#include <string>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class Gamepad {
  public:
    Gamepad(int id);

    std::string getName();
    void getState(GLFWgamepadstate& state);

  private:
    int m_id;
};

class Joystick {
  public:
    Joystick(int id);
    Joystick();

    inline int getID() const { return m_id; }

    bool isPresent();
    std::string getName();
    std::string getGUID();

    bool isGamepad();
    Gamepad& getGamepad();

  private:
    int m_id;
    Gamepad m_gamepad;
};

NS_SPECTRUM_END