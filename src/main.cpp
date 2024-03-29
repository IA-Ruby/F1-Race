// Alunos:  Francisco Eudes Mendes Filho - 470641
//          Luis Gustavo Giraum - 000024
//          Lamec               - :#&?@!

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "time.h"
#include "scene.cpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../header/stb_image.h"

int main(){

    stbi_set_flip_vertically_on_load(true);
    
    int width, height, nrChannels;
    unsigned int texId;
    unsigned char *data = stbi_load("car.jpg", &width, &height, &nrChannels, 0);

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMPILE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);   
    stbi_image_free(data);

    GLubyte colorCar[]     = {255, 240, 255};
    GLubyte colorRoad[]    = {255, 225, 131};
    GLubyte colorField[]   = {54, 186, 255};
    GLubyte colorBG[]      = {18, 1, 50};
    GLubyte colorLight[]   = {246, 44, 180};
    GLubyte colorSun[]     = {255, 225, 131};
    GLubyte colorLeaves[]  = {0, 255, 0};
    GLubyte colorWood[]    = {150, 100, 100};
    
    Scene scene(colorCar, colorSun, colorLight, colorField, colorBG, colorRoad, texId);

    sf::Time frameTime{sf::Time::Zero};
    sf::Clock clock;
    sf::Event ev;
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.antialiasingLevel = 4;  
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
    glFrustum(-ratio, ratio, -1.f, 1.f, 10.f, 120000.f);

    bool acl = false;
    bool nitro = false;
    bool brake = false;
    int direction = 0;

    while (window.isOpen())
    {
        scene.manageEvents(frameTime.asSeconds(), acl, nitro, brake, direction);

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
                direction = 0; 
            }
            if(ev.type == sf::Event::KeyPressed)
            {
                if(ev.key.code == sf::Keyboard::Escape ){ window.close();}
                if(ev.key.code == sf::Keyboard::Up     ){ acl = true; }
                if(ev.key.code == sf::Keyboard::Right  ){ direction =  1; }  
                if(ev.key.code == sf::Keyboard::Left   ){ direction = -1; }
                if(ev.key.code == sf::Keyboard::Down   ){ brake = true; }
                if(ev.key.code == sf::Keyboard::Space  ){ nitro = true; }
                if(ev.key.code == sf::Keyboard::Num1   ){ scene.setScene(1); }
                if(ev.key.code == sf::Keyboard::Num2   ){ scene.setScene(2); }
                if(ev.key.code == sf::Keyboard::Num3   ){ scene.setScene(3); }
                if(ev.key.code == sf::Keyboard::Num4   ){ scene.setScene(4); }
                if(ev.key.code == sf::Keyboard::Num5   ){ scene.setScene(5); }
            }
        }

        frameTime = clock.restart();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        scene.draw(frameTime.asSeconds());

        window.display();
    }
    return 0;
}