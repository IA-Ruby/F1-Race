#ifndef ROAD_H
#define ROAD_H

#include "../glm/vec3.hpp"
#include <deque>
#include "car.h"

#include "../glm/vec3.hpp"

using namespace std;

class Road
{
    private:
        deque<float> cordY;
        deque<Car> enemies;
        GLubyte colorRoad[3];
        GLubyte colorBG[3];
        unsigned int carTexId;
        void updRoad(float speed);
        void drawQuad(float x, float y);

    public:
        Road( GLubyte colorRoad[3], GLubyte colorBG[3]);
        void draw(float speed);
        void setCarTexId(unsigned int carTexId);
};

#endif