#pragma once
#include <string>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class SPL_API Joystick {
  public:
    Joystick(int id);
    Joystick();

    inline int getID() const { return m_id; }

    bool isPresent();
    std::string getName();
    std::string getGUID();

    bool isGamepad();
    std::string getGamepadName();
    void getGamepadState(GLFWgamepadstate& state);

  private:
    int m_id;
};

NS_SPECTRUM_END