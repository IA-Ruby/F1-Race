#ifndef TEXTURES_H
#define TEXTURES_H

#define TEX_CAR 0
#define TEX_TRAIN 1
#define TEX_RAILWAY 2
#define TEX_FLOOR 3
#define TEX_WALL 4
#define TEX_WALL2 5
#define TEX_WHEEL 6
#define TEX_WHEELCOLOR 7
#define TEX_CARFRONT 8
#define TEX_CARBACK 9
#define TEX_CARTOPFRONT 10
#define TEX_CARTOPBACK 11
#define TEX_CARTOP 12
#define TEX_CARWINDOW 13
#define TEX_CARTAIL 14
#define TEX_CARNUMBER 15

#include <SFML/Graphics.hpp>

class Textures
{
private:
    sf::Texture carTex;
    sf::Texture trainTex;
    sf::Texture railwayTex;
    sf::Texture floorTex;
    sf::Texture wallTex;
    sf::Texture wall2Tex;
    sf::Texture wheelTex;
    sf::Texture wheelColorTex;
    sf::Texture carFrontTex;
    sf::Texture carBackTex;
    sf::Texture carTopFrontTex;
    sf::Texture carTopBackTex;
    sf::Texture carTopTex;
    sf::Texture carWindowTex;
    sf::Texture carTailTex;
    sf::Texture carNumberTex;
    void loadTextures();
    sf::Texture *getTextureAddress(int type);

public:
    Textures();
    void bind(int texture);
    void unbind();
};

#endif