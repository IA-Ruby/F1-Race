// Aluno: Francisco Eudes Mendes Filho
// Matricula: 470641

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#
#include "../glm/glm.hpp"
#include "../glm/ext.hpp"
#include "time.h"

#include "../header/player.h"
#include "player.cpp"
#include "../header/horizon.h"
#include "horizon.cpp"
#include "../header/road.h"
#include "road.cpp"
#include "../header/field.h"
#include "field.cpp"

#define FPS 60

// Inicializando variaveis
float turn = 0;
float aux = 0;
bool acl = false;
bool brake = false;
bool camFree = false;
bool showMap = true;
bool showLines = false;

glm::vec3 camPosFree(100,-200,50);

// Defining Colors
GLubyte colorCar[]     = {255, 240, 255};
GLubyte colorRoad[]    = {255, 225, 131};
GLubyte colorField[]   = {54, 186, 255};
GLubyte colorBG[]      = {18, 1, 50};
GLubyte colorLight[]   = {246, 44, 180};
GLubyte colorSun[]     = {255, 225, 131};
GLubyte colorLeaves[]  = {0, 255, 0};
GLubyte colorWood[]    = {150, 100, 100};

// Criando os objetos
Player player(colorBG, colorCar, glm::vec3(0,0,0), 0.f);
Horizon horizon(colorSun, colorLight, colorField, colorBG, glm::vec3(0,19000,1000), 900.f);
Road road(colorRoad, colorBG, glm::vec3(0,0,0));
Field field(colorField, colorBG, colorLeaves, colorWood);

void draw(float time, glm::vec3 camPos){
    if(showMap){
        horizon.draw(camPos);
        field.draw(player.getSpeed(),showLines);
        road.draw(player.getSpeed(),showLines);
    }
    player.draw(showLines);
    glFlush();
}

int main(){
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.antialiasingLevel = 2;  
    contextSettings.stencilBits = 1;       
    
    // Criação da janela
    sf::Window window(sf::VideoMode(900, 600), "Synthwave Race",  sf::Style::Fullscreen, contextSettings);
    
    // Inicialização de algumas variaveis importantes
    sf::Time frameTime{sf::Time::Zero};
    sf::Clock clock;
    sf::Event ev;

    // Limitando o numero de quadros por segundo
    window.setFramerateLimit(FPS);
    window.setActive();
    glClearDepth(1.f);
    // Mudando a cor para não precisar desenhar um quadrado no fundo depois
    glClearColor(   colorBG[0]/255.f,
                    colorBG[1]/255.f,
                    colorBG[2]/255.f, 1);

    //  Habilitando o uso do Alpha
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);
    
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 10.f, 20000.f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    

    while (window.isOpen()){

        //  Os tratamentos de eventos são realizados no loop principal e não no loop de eventos para evitar delay           
        if(brake) player.brake(frameTime.asSeconds());
        if(!acl)player.slowDown(frameTime.asSeconds());
            else if(turn!=0) player.turn(turn, frameTime.asSeconds());
                else player.speedUp(frameTime.asSeconds());
        
        while (window.pollEvent(ev)){
            switch(ev.type){
                case sf::Event::Closed:
                    window.close(); 
                    break;
                case sf::Event::KeyReleased:
                    clock.restart(); 
                    acl = false;
                    brake = false;
                    turn = 0;
                    break;
                case sf::Event::KeyPressed:
                    switch(ev.key.code){
                        case sf::Keyboard::Escape: 
                            window.close(); 
                            break;
                        case sf::Keyboard::Up: 
                            acl = true;
                            break;
                        case sf::Keyboard::Left:
                            acl = true;
                            turn = -5;        
                            break;
                        case sf::Keyboard::Right:
                            acl = true;
                            turn = 5;
                            break;
                        case sf::Keyboard::Down:
                            acl = false;
                            brake = true;
                            break;
                        case sf::Keyboard::Z:
                            camPosFree.z += 10;
                            break;
                        case sf::Keyboard::X:
                            camPosFree.z -= 10;
                            break;
                        case sf::Keyboard::A:
                            camPosFree.y += 10;
                            break;
                        case sf::Keyboard::S:
                            camPosFree.y -= 10;
                            break;
                        case sf::Keyboard::Q:
                            camPosFree.x += 10;
                            break;
                        case sf::Keyboard::W:
                            camPosFree.x -= 10;
                            break;
                        case sf::Keyboard::C:
                            if(camFree)
                                camFree = false;
                            else
                                camFree = true;
                            break;
                        case sf::Keyboard::B:
                            if(showMap)
                                showMap = false;
                            else
                                showMap = true;
                            break;
                        case sf::Keyboard::V:
                            if(showLines)
                                showLines = false;
                            else
                                showLines = true;
                            break;
                        case sf::Keyboard::R:
                                camPosFree = glm::vec3(100,-200,50);
                            break;
                    }
                break;
            }
        }

        frameTime = clock.restart();
         
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        if(camFree){ 
            glm::mat4 matrizCameraFree =    glm::lookAt(camPosFree,                            
                                            glm::vec3(0,0,0),   
                                            glm::vec3(0,0,1));

            glMultMatrixf(glm::value_ptr(matrizCameraFree));
            draw(frameTime.asSeconds(), camPosFree); 

        }else{
            glm::vec3 camPos =  {player.getCarPos().x,            // Alinhado com o carro no eixo X
                                (player.getCarPos().y) - 300,     // Atrás do carro no eixo Y
                                (player.getCarPos().z) + 20};     // Acima do carro no eixo Z

            glm::mat4 matrizCamera =    glm::lookAt(camPos,                             
                                        glm::vec3(camPos[0], (camPos[1]+1), (camPos[2])),   
                                        glm::vec3(0,0,1));

            glMultMatrixf(glm::value_ptr(matrizCamera));
            draw(frameTime.asSeconds(), camPos); 
        }

        window.display();
    }
    return 0;
}