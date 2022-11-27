#include "../header/driver.h"

// Accelerador - Aumenta gradativamente a velocidade do carro
void Driver::speedUp(float time)
{
    if (speed < maxSpeed)
    {
        speed += (speed / 2 + 20.f) * time;
 
        if (speed > maxSpeed)
        {
            speed = maxSpeed;
        }
    }
}

// Nitro - VRUUUUUUUUUUUUM
void Driver::nitro(float time)
{
    if (speed < maxSpeed*1.5)
    {
        speed += (speed + 20.f) * time;
  
        if (speed > maxSpeed*1.5)
        {
            speed = maxSpeed*1.5;
        }
    }   
}

// Freio - Reduz rapidamente a velocidade do carro
void Driver::brake(float time)
{
    if (speed > 0)
    {
        speed -= 200 * time;
        if (speed < 0)
        {
            speed = 0;
        }
    }
}

// Não fazer nada - o carro deminui de velocidade lentamente
void Driver::slowDown(float time)
{
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
void Driver::turn(int direction)
{
    this->direction = direction;
    rotZ = (10.f * (speed / 100)) * -direction;
    if(rotZ > 15)
    {
        rotZ = 15;
    } 
    if(rotZ < -15)
    {
        rotZ = -15;
    }
    
}