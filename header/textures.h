#ifndef TEXTURES_H
#define TEXTURES_H

#define TEX_CAR 0

#include <SFML/Graphics.hpp>

class Textures
{
    private:
        sf::Texture carTex;
        void loadTextures();
    public:
        Textures();
        sf::Texture* getTextureAddress(int type);
};

#endif