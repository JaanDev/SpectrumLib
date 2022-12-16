#pragma once
#include "raylib.h"

class Scene {
    protected:
        Color m_cBGColor = WHITE;
    public:
        //Scene* create();
        Scene();
        Color getColor();
};