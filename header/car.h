#ifndef CAR_H
#define CAR_H

#include <GL/glu.h>
#include <math.h>
#include "textures.h"
#include "../glm/vec3.hpp"

#define M_PI 3.14159265358979323846

using namespace glm;

class Car
{
    protected:
        GLubyte colorCar[3];
        GLubyte colorOutline[3];
        vec3 carPos;
        float maxSpeed;
        float speed = 0;
        float rotZ = 0;
        float rotX = 0;
        float wheelRot = 0;
        float angle = 0; 
        int direction = 0;
        Textures* textures;
        void drawMode(int mode, GLubyte color[3]);
        void drawWheel(float radius, float width);
        void drawQuadStrip(float radius1, float radius2, float widht1, float witdh2);
        
    public:
        Car(GLubyte colorCar[3], GLubyte colorOutline[3], vec3 carPos, float maxSpeed, Textures* textures);
        void draw();
        void colision(int type);
        float getSpeed();
        vec3 getCarPos();
        int getDirection();
        void setCarRotZ(float rotZ);
        void setCarRotX(float rotX);
        void setCarPos(vec3 carPos);
        void setCarPosX(float carPos);
        void setCarPosZ(float carPos);
        void setCarPosY(float carPos);
        void setDirection(int direction);
};

#endif