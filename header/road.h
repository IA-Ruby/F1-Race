#ifndef ROAD_H
#define ROAD_H

#include "../glm/vec3.hpp"
#include <deque>
#include "car.h"

using namespace std;

class Road{
    private:
        deque<float> cordY;
        deque<Car> enemies;
        GLubyte colorRoad[3];
        GLubyte colorBG[3];
        glm::vec3 roadPos;
        void updRoad(float speed);
        void drawQuad(float x, float y);
    public:
        Road(   GLubyte colorRoad[3],
                GLubyte colorBG[3], 
                glm::vec3 roadPos);
        void draw(float speed, bool show);
};

#endif