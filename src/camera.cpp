#include "../header/camera.h"
#include <GL/gl.h>

Camera::Camera(vec3 camPos, vec3 camLookAt, vec3 camTop)
{
    this->camPos = camPos;
    this->camLookAt = camLookAt;
    this->camTop = camTop;
}

void Camera::rotateCam(float amount, vec3 axis)
{
    // camLookAt = rotate(camLookAt, amount, axis);
    // n funciona ;-;
}

void Camera::translateCam(vec3 camPos)
{
    this->camPos += camPos;
    this->camLookAt += camPos;
}

void Camera::setCamPos(vec3 camPos)
{
    this->camPos = camPos;
}

void Camera::setCamLookAt(vec3 camLookAt)
{
    this->camLookAt = camLookAt;
}

mat4 Camera::getCamera()
{
    mat4 camView = lookAt(camPos, camLookAt, camTop);
    return camView;
}

vec3 Camera::getCamPos()
{
    return camPos;
}