#pragma once

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

class Game{
    private: 
        //Variables 
        //Window
        sf::Window* window;
        sf::VideoMode videomode;
        sf::ContextSettings contextSettings;
        sf::Event ev;

        //Private functions
        void initVariables();
        void initWindow();

    public: //Public functions
        
        //Constructors and Destructors
        Game(); 

        //Accessors
        const bool running() const; 
        
        //Functions
        void pollEvents();
        void update();
        void render();
};