#include "../header/player.h"

#include <GL/gl.h>
#include <math.h>

// Freio - Reduz rapidamente a velocidade do carro
void Player::brake(float time)
{
    rot = 0;
    if (speed > 0)
    {
        speed -= 200 * time;
        if (speed < 0)
        {
            speed = 0;
        }
    }
}

// Accelerador - Aumenta gradativamente a velocidade do carro
void Player::speedUp(float time)
{
    float max = 200;
    rot = 0;
    if (speed < max)
    {
        speed += (speed / 2 + 20.f) * time;
        if (speed > max)
        {
            speed = max;
        }
    }
}

void Player::nitro(float time)
{
    float max = 400;
    rot = 0;
    if (speed < max)
    {
        speed += (speed + 20.f) * time;
        if (speed > max)
        {
            speed = max;
        }
    }   
}
// Não fazer nada - o carro deminui de velocidade lentamente
void Player::slowDown(float time)
{
    rot = 0;
    if (speed > 0)
    {
        speed -= 20.0f * time;
        if (speed < 0)
        {
            speed = 0;
        }
    }
}

// Girar - O carro se desloca para direita ou esquerda e rotaciona
void Player::turn(float dist, bool move)
{
    float max = 60;
    if (carPos.x + (dist * (speed / 3)) <= max && carPos.x + (dist * (speed / 3)) >= -max)
    {
        if (move)
            carPos.x += dist * (speed / 3);
        if (dist > 0)
        {
            rot = -10.f * ((speed / 100));
            if(rot < -20)
            {
                rot = -20;
            }
        }
        else
        {
            rot = 10.f * ((speed / 100));
            if(rot > 20)
            {
                rot = 20;
            }
        }
    }
    else if (dist > 0)
    {
        carPos.x = max;
        rot = 0;
    }
    else
    {
        carPos.x = -max;
        rot = 0;
    }
}
