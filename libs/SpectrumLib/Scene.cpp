#include "Scene.h"

Scene::Scene(){
    this->m_cBGColor = WHITE;
}

//Scene* Scene::create(){
//    static Scene* scene = new Scene();
//    return scene;
//}

Color Scene::getColor(){
    return this->m_cBGColor;
}