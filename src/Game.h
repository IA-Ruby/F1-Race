#pragma once

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

class Game{
    //Variables 
    //Window
    sf::Window* window;
    sf::VideoMode videomode;
    sf::ContextSettings contextSettings;
    sf::Event ev;
    sf::Clock clock;

    private: //Private functions
        void initVariables();
        void initWindow();

    public: //Public functions
        
        //Constructors and Destructors
        Game(); 
        virtual ~Game();

        //Accessors
        const bool running() const; 
        
        //Functions
        void pollEvents();
        void update();
        void render();
};