#ifndef CAMERA_H
#define CAMERA_H

#include "../glm/vec3.hpp"
#include "../glm/mat4x4.hpp"
#include "../glm/ext.hpp"

using namespace glm;

class Camera
{
    private:
        vec3 camPos;
        vec3 camLookAt;
        vec3 camTop;
    
    public:
        Camera();
        void rotateCam(float amount, vec3 axis);
        void translateCam(vec3 camPos);
        void setCamPos(vec3 camPos);
        void setCamPosX(float camPos);
        void setCamPosY(float camPos);
        void setCamPosZ(float camPos);
        void setCamLookAt(vec3 camLookAt);
        mat4 getCamera();
        vec3 getCamPos();
};

#endif