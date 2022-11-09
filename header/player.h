#ifndef PLAYER_H
#define PLAYER_H

#include "../glm/vec3.hpp"

#define _USE_MATH_DEFINES

#include "car.h"
#include "../src/car.cpp"

class Player: public Car
{
    public:
        using Car::Car;
        void brake(float time);
        void speedUp(float time);
        void nitro(float time);
        void slowDown(float time);
        void turn(float dist, bool move);
};

#endif