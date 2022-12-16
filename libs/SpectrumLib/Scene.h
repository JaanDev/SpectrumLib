#ifndef __SPECTRUM__SCENE_H__
#define __SPECTRUM__SCENE_H__

#include "includes.h"


class Scene {
protected:
    Color m_cBGColor = WHITE;
public:
    //Scene* create();
    Scene();
    Color getColor();
};

#endif