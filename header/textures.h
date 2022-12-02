#ifndef TEXTURES_H
#define TEXTURES_H

#define TEX_CAR 0
#define TEX_TRAIN 1
#define TEX_RAILWAY 2

#include <SFML/Graphics.hpp>

class Textures
{
    private:
        sf::Texture carTex;
        sf::Texture trainTex;
        sf::Texture railwayTex;
        void loadTextures();
        sf::Texture* getTextureAddress(int type);
    public:
        Textures();
        void bind(int texture);
        void unbind();
};

#endif