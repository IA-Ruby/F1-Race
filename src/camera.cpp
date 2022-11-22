#include "../header/camera.h"

Camera::Camera()
{
    mat4 Model(1.0f);
    this->camPos = vec3(0,0,0);
    this->camLookAt = vec3(0,0,0);
    this->camTop = vec3(0,0,1);
}

void Camera::rotateCam(float amount, vec3 axis)
{
    // Model = rotate(mat4(1.0f), radians(amount), axis);
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

void Camera::setCamPosX(float camPos)
{
    this->camPos.x = camPos;
}

void Camera::setCamPosY(float camPos)
{
    this->camPos.y = camPos;
}

void Camera::setCamPosZ(float camPos)
{
    this->camPos.z = camPos;
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