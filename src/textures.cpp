#include "../header/textures.h"

Textures::Textures()
{
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMPILE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    loadTextures();
}

void Textures::loadTextures()
{
    string filename;

    filename = "car.jpg";
    if (!this->carTex.loadFromFile(filename)) throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carTex.generateMipmap()) throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carTex.setSmooth(true);

    filename = "train.png";
    if (!this->trainTex.loadFromFile(filename)) throw "Erro: Falha ao carregar textura " + filename;
    if (!this->trainTex.generateMipmap()) throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->trainTex.setSmooth(true);

    filename = "railway.jpg";
    if (!this->railwayTex.loadFromFile(filename)) throw "Erro: Falha ao carregar textura " + filename;
    if (!this->railwayTex.generateMipmap()) throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->railwayTex.setSmooth(true);
}

sf::Texture* Textures::getTextureAddress(int type)
{
    switch (type)
    {
        case (TEX_CAR): return &this->carTex;
        case (TEX_TRAIN): return &this->trainTex;
        case (TEX_RAILWAY): return &this->railwayTex;
        default: return NULL;
    }
}

void Textures::bind(int texture)
{
    sf::Texture::bind(getTextureAddress(texture));
}

void Textures::unbind()
{
    sf::Texture::bind(NULL);
}