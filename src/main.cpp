// Alunos:  Francisco Eudes Mendes Filho - 470641
//          Luis Gustavo Giraum - 000024
//          Lamec               - :#&?@!

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "../glm/glm.hpp"
#include "../glm/ext.hpp"
#include "time.h"
#include "../header/stb_image.h"
#include <vector>

#include "player.cpp"
#include "scene.cpp"
#include "camera.cpp"

// Inicializando variaveis
float turn = 0;
bool acl = false;
bool nitro = false;
bool brake = false;
int number = 0;
int moveCar = true;

// Definindo cores
GLubyte colorCar[]     = {255, 240, 255};
GLubyte colorRoad[]    = {255, 225, 131};
GLubyte colorField[]   = {54, 186, 255};
GLubyte colorBG[]      = {18, 1, 50};
GLubyte colorLight[]   = {246, 44, 180};
GLubyte colorSun[]     = {255, 225, 131};
GLubyte colorLeaves[]  = {0, 255, 0};
GLubyte colorWood[]    = {150, 100, 100};

// Criando os objetos
Player player( colorBG, colorCar, glm::vec3(0,0,0), 0.f);
Scene scene( colorSun, colorLight, colorField, colorBG, colorRoad);
Camera cam( vec3(0,-300,50), vec3(0, -299, 50), vec3(0,0,1));

void draw(){
    scene.draw(number, player.getSpeed(), turn, cam.getCamPos());
    moveCar = scene.carShouldMove();
    if(!moveCar)
    {
        player.setCarPos(vec3(0, 0, 0));
    }
    player.draw();
}

void manageEvents(float time)
{
    if (nitro)
    {
        player.nitro(time);

        if (cam.getCamPos().y > -400)
        {
            cam.setCamPos(vec3(cam.getCamPos().x,cam.getCamPos().y - (100 * time), cam.getCamPos().z));
        }
        else if (cam.getCamPos().y < -400)
        {
            cam.setCamPos(vec3(cam.getCamPos().x,  -400, cam.getCamPos().z));
        }
    }
    else
    {
        if (cam.getCamPos().y < -300)
        {
            cam.setCamPos(vec3(cam.getCamPos().x, cam.getCamPos().y + (100 * time), cam.getCamPos().z));
        }
        else if (cam.getCamPos().y > -300)
        {
            cam.setCamPos(vec3(cam.getCamPos().x, -300, cam.getCamPos().z));
        }

        if (acl)
        {
            if (player.getSpeed() < 200)
            {
                player.speedUp(time);
            }
            else
            {
                player.slowDown(time);
            }
        }
        else if (turn != 0)
        {
            player.turn(turn * time, moveCar);
        }
        else if (brake)
        {
            player.brake(time);
        }
        else
        {
            player.slowDown(time);
        }
    }
}

void setCamera()
{
    cam.setCamPos(vec3(player.getCarPos().x, cam.getCamPos().y, 20));
    cam.setCamLookAt(vec3(player.getCarPos().x, cam.getCamPos().y + 1, 20));
    glMultMatrixf(glm::value_ptr(cam.getCamera()));
}

int main(){
    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../textures/car.jpg", &width, &height, &nrChannels, 0);
    if(data) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);   
    else return -1;
    stbi_image_free(data);

    sf::Time frameTime{sf::Time::Zero};
    sf::Clock clock;
    sf::Event ev;
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.    antialiasingLevel = 4;  
    contextSettings.stencilBits = 1;       
    
    sf::Window window(sf::VideoMode(900, 600), "Synthwave Race",  sf::Style::Fullscreen, contextSettings);

    window.setFramerateLimit(60);
    window.setActive();
    glClearDepth(1.f);
    glClearColor(colorBG[0]/255.f, colorBG[1]/255.f, colorBG[2]/255.f, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 10.f, 40000.f);

    while (window.isOpen())
    {
        manageEvents(frameTime.asSeconds());

        while (window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
            { 
                window.close(); 
            }
            if(ev.type == sf::Event::KeyReleased)
            { 
                clock.restart(); 
                acl = false;
                nitro = false; 
                brake = false; 
                turn = 0; 
            }
            if(ev.type == sf::Event::KeyPressed)
            {
                if(ev.key.code == sf::Keyboard::Escape ){ window.close();}
                if(ev.key.code == sf::Keyboard::Up     ){ acl = true; }
                if(ev.key.code == sf::Keyboard::Right  ){ turn = 5; }  
                if(ev.key.code == sf::Keyboard::Left   ){ turn = -5; }
                if(ev.key.code == sf::Keyboard::Down   ){ brake = true; }
                if(ev.key.code == sf::Keyboard::Space  ){ nitro = true; }
                if(ev.key.code == sf::Keyboard::Q      ){ number = 0; }
                if(ev.key.code == sf::Keyboard::Num1   ){ number = 1; }
                if(ev.key.code == sf::Keyboard::Num2   ){ number = 2; }
                if(ev.key.code == sf::Keyboard::Num3   ){ number = 3; }
                if(ev.key.code == sf::Keyboard::Num4   ){ number = 4; }
                if(ev.key.code == sf::Keyboard::Num5   ){ number = 5; }    
            }
        }

        frameTime = clock.restart();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        setCamera();
        
        draw();

        window.display();
    }
    return 0;
}