#include "Game.h"

//Private functions
void Game::initVariables(){
    this->window = nullptr;
}

void Game::initWindow(){
    this->videomode.height = 560;
    this->videomode.height = 800;
    this->contextSettings.depthBits = 24;
    this->window = new sf::Window(this->videomode, "F1-Race", sf::Style::Titlebar | sf::Style::Close, this->contextSettings);
}

//Constructors and Destructors
Game::Game(){
    this->initVariables();
    this->initWindow();
}

Game::~Game(){
    delete this->window; 
}

//Accessors
const bool Game::running() const{
    return this->window->isOpen();
}

//Functions
void Game::pollEvents(){
     // Process events
    while (this->window->pollEvent(this->ev)){
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                switch(this->ev.key.code){
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;
                    case sf::Keyboard::Up:
                        glRotated(10,0,1,0);
                        //Speed up
                        break;
                    case sf::Keyboard::Down:
                        //Brake
                        break;
                    case sf::Keyboard::Right:
                        //Turn right
                        break;
                    case sf::Keyboard::Left:
                        //Turn left
                        break;
                    default:
                        //lower speed
                        break;
                }
                break;
        }
    }
}

void Game::update(){
    this->pollEvents();
}

void Game::render(){

    /*

    this->window->setActive();

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Disable lighting and texturing
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, this->window->getSize().x, this->window->getSize().y);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(this->window->getSize().x) / this->window->getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    // Disable normal and texture coordinates vertex components
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);  
        glBegin(GL_QUADS); //a cada quatro pontos, conecte-os em quadriláteros
            glVertex3f( -100, -100,-30);
            glVertex3f( -100, 100,-30);
            glVertex3f( 100, 100,-30);
            glVertex3f( 100, -100,-30);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);  
        glBegin(GL_QUADS); //a cada quatro pontos, conecte-os em quadriláteros
            glVertex3f( -10, -100,-20);
            glVertex3f( -10, 100,-20);
            glVertex3f( 10, 100,-20);
            glVertex3f( 10, -100,-20);
        glEnd();
        glPopMatrix();

        // Draw the game
        glDrawArrays(GL_TRIANGLES, 0, 36);

        */
        this->window->setActive();
        glClearColor(255,5,5,255);

        this->window->display();
}