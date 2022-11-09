#ifndef SCENE_H
#define SCENE_H

#include "horizon.h"
#include "road.h"
#include "field.h"
#include "finalRoad.h"
#include "trainTunnel.h"
#include "funnyTunnel.h"

#include "../src/horizon.cpp"
#include "../src/road.cpp"
#include "../src/field.cpp"
#include "../src/finalRoad.cpp"
#include "../src/trainTunnel.cpp"
#include "../src/funnyTunnel.cpp"

using namespace glm;

class Scene
{
    private:
        Horizon horizon;
        Field field;
        Road road;
        FinalRoad final;
        Horizon finalHorizon;
        TrainTunnel trainTunnel;
        FunnyTunnel funnyTunnel;
        float finish;
        int number;
        bool moveCar;
        void changeScene(float speed);
    
    public:
        Scene(GLubyte colorSun[3], GLubyte colorLight[3], GLubyte colorField[3], GLubyte colorBG[3], GLubyte colorRoad[3]);
        void draw(int number, float speed, float turn, vec3 camPos);
        bool carShouldMove();        
};

#endif