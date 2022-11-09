#ifndef CAR_H
#define CAR_H

#include "../glm/vec3.hpp"

class Car
{
    protected:
        GLubyte colorCar[3];
        GLubyte colorOutline[3];
        glm::vec3 carPos;
        float rot = 0;
        float auxRot = 0;
        float speed;
        unsigned int texId;
        void drawMode(int mode, GLubyte color[3]);
        void drawWheel(float radius, float width);
  
    public:
        Car(GLubyte colorCar[3], GLubyte colorOutline[3], glm::vec3 carPos, float speed);
        Car(GLubyte colorCar[3], glm::vec3 carPos, float speed);
        void draw();
        float getSpeed();
        glm::vec3 getCarPos();
        void setCarPos(glm::vec3 carPos);
        void setCarPos(float carPos);
        void setTexId(unsigned int texId);
};

#endif