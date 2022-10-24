#ifndef CAR_H
#define CAR_H

#include "../glm/vec3.hpp"

class Car{
    protected:
        GLubyte colorCar[3];
        GLubyte colorOutline[3];
        glm::vec3 carPos;
        float rot = 0;
        float auxRot = 0;
        float speed;
        void drawMode(int mode, GLubyte color[3], bool show);
        void drawWheel(float radius, float width, GLubyte color[3]);
    public:
        Car(    GLubyte colorCar[3], 
                GLubyte colorOutline[3], 
                glm::vec3 carPos, 
                float speed);
        Car(    GLubyte colorCar[3],
                glm::vec3 carPos, 
                float speed);
        void draw(bool show);
        float getSpeed();
        glm::vec3 getCarPos();
        void setCarPos(float carPos);
};

#endif