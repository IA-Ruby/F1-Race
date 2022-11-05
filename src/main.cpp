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
#include "player.cpp"
#include "horizon.cpp"
#include "road.cpp"
#include "field.cpp"
#include "finalRoad.cpp"
#include "trainTunnel.cpp"
#include "funnyTunnel.cpp"
#include "camera.cpp"

// Inicializando variaveis
float turn = 0;
bool acl = false;
bool brake = false;
bool moveCar = true;
bool camFree = false;
bool showLines = false;
int scene = 0;
int camType = 1;
float auxRot = 0;

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
Camera cam(vec3(100,-200,50), vec3(100, -199, 50), vec3(0,0,1));
Player player(colorBG, colorCar, glm::vec3(0,0,0), 0.f);
Horizon horizon(colorSun, colorLight, colorField, colorBG, glm::vec3(0,19500,1000), 900.f, true, true);
Road road(colorRoad, colorBG, glm::vec3(0,0,0));
Field field(colorField, colorBG);
FinalRoad final(colorLight, colorBG);
Horizon finalHorizon(colorSun, colorLight, colorField, colorBG, glm::vec3(0,19500,0), 1500.f, false, false);
TrainTunnel trainTunnel(colorSun, colorField, colorBG);
FunnyTunnel funnyTunnel(colorSun, colorBG);

void draw(float time, glm::vec3 camPos){
    if (scene == 1)
    {
        horizon.draw(camPos);
        field.draw(player.getSpeed());
        road.draw(player.getSpeed());
        moveCar = true;
    }
    else if (scene == 2)
    {
        final.draw(player.getSpeed());
        finalHorizon.draw(camPos);
        moveCar = false;
    }
    else if (scene == 3)
    {
        trainTunnel.draw(player.getSpeed());
        moveCar = true;
    }
    else if (scene == 4)
    {
        player.setCarPos(vec3(0, 0, 0));
        funnyTunnel.draw(player.getSpeed(), turn);
        moveCar = false;
    }
    else if (scene == 5)
    {
        // Spiral
    }
    player.draw();
}

void setCamera(){
    if (camType == 1)
    {
        cam.setCamPos(vec3(player.getCarPos().x, player.getCarPos().y - 300, player.getCarPos().z + 20));
        cam.setCamLookAt(vec3(player.getCarPos().x, player.getCarPos().y - 299, player.getCarPos().z + 20));
    }
    else if (camType == 2)
    {
        cam.setCamPos(vec3(player.getCarPos().x, player.getCarPos().y + 2, player.getCarPos().z + 20));
        cam.setCamLookAt(vec3(player.getCarPos().x, player.getCarPos().y + 3, player.getCarPos().z + 18));
    }
    glMultMatrixf(glm::value_ptr(cam.getCamera()));
}

int main(){
    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
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
    glFrustum(-ratio, ratio, -1.f, 1.f, 10.f, 40000.f);

    while (window.isOpen())
    {
           
        if(acl)             player.speedUp(frameTime.asSeconds());
        else if(turn!=0)    player.turn(turn*frameTime.asSeconds(), moveCar);
        else if(brake)      player.brake(frameTime.asSeconds());
        else                player.slowDown(frameTime.asSeconds());
        
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
                if(ev.key.code == sf::Keyboard::I      ){ camType = 1; }
                if(ev.key.code == sf::Keyboard::O      ){ camType = 2; }
                if(ev.key.code == sf::Keyboard::Num1   ){ scene = 1; }
                if(ev.key.code == sf::Keyboard::Num2   ){ scene = 2; }
                if(ev.key.code == sf::Keyboard::Num3   ){ scene = 3; }
                if(ev.key.code == sf::Keyboard::Num4   ){ scene = 4; }
                if(ev.key.code == sf::Keyboard::Num5   ){ scene = 5; }    
            }
        }

        frameTime = clock.restart();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        setCamera();
        draw(frameTime.asSeconds(), cam.getCamPos());
        window.display();
    }
    return 0;
}

// #include Game.h 
// 
// int main()
// {
// 	srand(static_cast<unsigned>(time(0)));

// 	Game game;

// 	while (game.getWindow().isOpen())
// 	{
// 		game.update();
// 		game.render();
// 	}

// 	//End of application
// 	return 0;
// }