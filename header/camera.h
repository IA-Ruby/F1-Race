#ifndef CAMERA_H
#define CAMERA_H

#include "../glm/glm.hpp"

using namespace glm;

class Camera
{
    private:
        vec3 camPos;
        vec3 camLookAt;
        vec3 camTop;
    
    public:
        Camera(vec3 camPos, vec3 camLookAt, vec3 camTop);
        void rotateCam(float amount, vec3 axis);
        void translateCam(vec3 camPos);
        void setCamPos(vec3 camPos);
        void setCamLookAt(vec3 camLookAt);
        mat4 getCamera();
        vec3 getCamPos();
};

#endif