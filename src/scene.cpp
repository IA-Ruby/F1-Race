#include "../header/scene.h"
#include <GL/gl.h>

Scene::Scene(GLubyte colorSun[3], GLubyte colorLight[3], GLubyte colorField[3], GLubyte colorBG[3], GLubyte colorRoad[3])
:
    horizon( colorSun, colorLight, colorField, colorBG, glm::vec3(0,39000,2000), 1800.f, true, true),
    road( colorRoad, colorBG),
    field( colorField, colorBG),
    final( colorLight, colorBG),
    finalHorizon( colorSun, colorLight, colorField, colorBG, glm::vec3(0,39500,0), 1800.f, false, false),
    trainTunnel( colorSun, colorField, colorBG),
    funnyTunnel( colorSun, colorBG)
{
    finish = 36000;
    number = 1;
    moveCar = true;
}

void Scene::draw(int number, float speed, float turn, vec3 camPos)
{
    if (number == 0)
    {
        number = this->number;
        changeScene(speed);
    }
    
    if (number == 1) 
    {
        horizon.draw(camPos);
        field.draw(speed);
        road.draw(speed);
        moveCar = true;
    }
    
    if (number == 2)
    {
        final.draw(speed);
        finalHorizon.draw(camPos);
        moveCar = false;
    }
    
    if (number == 3)
    {
        trainTunnel.draw(speed);
        moveCar = true;
    }
    
    if (number == 4)
    {
        funnyTunnel.draw(speed, turn);
        moveCar = false;
    }
    
    if (number == 5)
    {
        // Spiral
    }
}

bool Scene::carShouldMove()
{
    if(moveCar)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Scene::changeScene(float speed)
{
    if (number == 5)
    {
        number = 0;
    }

    if (finish <= 0)
    {
        number += 1;
        finish = 36000;
    }
    else
    {
        finish -= speed;
    }
}