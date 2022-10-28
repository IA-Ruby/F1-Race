// Aluno: Francisco Eudes Mendes Filho
// Matricula: 470641

#include <SFML/Window.hpp>
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

#define FPS 60

// Inicializando variaveis
float turn = 0;
bool acl = false;
bool brake = false;
bool camFree = false;
bool showLines = false;

int scene = 0;

glm::vec3 camPos(100,-200,50);

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
Horizon horizon(colorSun, colorLight, colorField, colorBG, glm::vec3(0,19500,1000), 900.f, true, true);
Road road(colorRoad, colorBG, glm::vec3(0,0,0));
Field field(colorField, colorBG, colorLeaves, colorWood);
FinalRoad final(colorLight, colorBG);
Horizon finalHorizon(colorSun, colorLight, colorField, colorBG, glm::vec3(0,19500,0), 1500.f, false, false);

void draw(float time, glm::vec3 camPos, int texId){
    if(scene == 1){
        horizon.draw(camPos);
        field.draw(player.getSpeed(), showLines);
        road.draw(player.getSpeed(), texId);
    }else if(scene == 2){
        final.draw(player.getSpeed());
        finalHorizon.draw(camPos);
    }else if(scene == 3){

    }else if(scene == 4){

    }else if(scene == 5){
        
    }
    player.draw(texId);
    glFlush();
}

int main(){
    // Criando a textura do carro
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../textures/car.jpg", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);   
    }else{
        return 1;
    }
    stbi_image_free(data);

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
            if(ev.type == sf::Event::Closed){ window.close(); }
            if(ev.type == sf::Event::KeyReleased){ clock.restart(); acl = false; brake = false; turn = 0; }
            if(ev.type == sf::Event::KeyPressed){
                if(ev.key.code == sf::Keyboard::Escape ){ window.close();}
                if(ev.key.code == sf::Keyboard::Up     ){ acl = true; }
                if(ev.key.code == sf::Keyboard::Right  ){ acl = true; turn = 5; }  
                if(ev.key.code == sf::Keyboard::Left   ){ acl = true; turn = -5; }
                if(ev.key.code == sf::Keyboard::Down   ){ acl = false; brake = true; }
                if(ev.key.code == sf::Keyboard::V      ){ showLines = !showLines; }
                if(ev.key.code == sf::Keyboard::C      ){ camFree = !camFree; }
                if(ev.key.code == sf::Keyboard::Z      ){ camPos.z += 20; }
                if(ev.key.code == sf::Keyboard::X      ){ camPos.z -= 20; }
                if(ev.key.code == sf::Keyboard::A      ){ camPos.y += 20; }
                if(ev.key.code == sf::Keyboard::S      ){ camPos.y -= 20; }
                if(ev.key.code == sf::Keyboard::Q      ){ camPos.x += 20; }
                if(ev.key.code == sf::Keyboard::W      ){ camPos.x -= 20; }
                if(ev.key.code == sf::Keyboard::R      ){ camPos = glm::vec3(100,-200,50); }
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
        
        glm::vec3 camPosAux(camPos);
        glm::vec3 lookAtAux(0,0,0);
        if(!camFree){
            camPosAux = {player.getCarPos().x, player.getCarPos().y - 300,player.getCarPos().z + 20};        
            lookAtAux = {camPosAux[0], camPosAux[1]+1, camPosAux[2]};
        }      
        glm::mat4 matrizCamera = glm::lookAt(camPosAux, glm::vec3(lookAtAux), glm::vec3(0,0,1));
        glMultMatrixf(glm::value_ptr(matrizCamera));
        
        draw(frameTime.asSeconds(), camPosAux, texture);

        window.display();
    }
    return 0;
}