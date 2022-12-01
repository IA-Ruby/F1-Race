#include "../header/textures.h"

Textures::Textures()
{
    loadTextures();
}

void Textures::loadTextures()
{
    if (!this->carTex.loadFromFile("car.jpg")) throw "Erro: Falha ao carregar textura.";
    this->carTex.setSmooth(true);
}

sf::Texture* Textures::getTextureAddress(int type)
{
    switch (type)
    {
        case (TEX_CAR): return &this->carTex;
        default: return NULL;
    }
}