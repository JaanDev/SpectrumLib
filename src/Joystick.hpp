#pragma once
#include <string>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class Joystick {
  public:
    Joystick(int id);
    Joystick();

    inline int getID() const { return m_id; }

    bool isPresent();
    std::string getName();
    std::string getGUID();

    bool isGamepad();

  private:
    int m_id;
};

NS_SPECTRUM_END