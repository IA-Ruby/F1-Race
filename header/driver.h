#ifndef DRIVER_H
#define DRIVER_H

#include "../src/car.cpp"

class Driver : public Car
{
    public:
        using Car::Car;
        void speedUp(float time);
        void nitro(float time);
        void brake(float time);
        void slowDown(float time);
        void turn(int direction);
};

#endif