#pragma once
#include "raylib.h"

class Scene {
    private:
        Color m_cBGColor = {255, 255, 255, 255};

    public:
        Color getColor();
};