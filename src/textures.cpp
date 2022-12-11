#include "../header/textures.h"

Textures::Textures()
{
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    loadTextures();
}

void Textures::loadTextures()
{
    string filename;

    filename = "train.png";
    if (!this->trainTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->trainTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->trainTex.setSmooth(true);

    filename = "railway.jpg";
    if (!this->railwayTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->railwayTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->railwayTex.setSmooth(true);

    filename = "floor.jpg";
    if (!this->floorTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->floorTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->floorTex.setSmooth(true);

    filename = "wall.jpg";
    if (!this->wallTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->wallTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->wallTex.setSmooth(true);

    filename = "wall2.jpeg";
    if (!this->wall2Tex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->wall2Tex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->wall2Tex.setSmooth(true);

    filename = "wheel.jpg";
    if (!this->wheelTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->wheelTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->wheelTex.setSmooth(true);

    filename = "wheelColor.jpg";
    if (!this->wheelColorTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->wheelColorTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->wheelColorTex.setSmooth(true);

    filename = "carFront.png";
    if (!this->carFrontTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carFrontTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carFrontTex.setSmooth(true);

    filename = "carBack.png";
    if (!this->carBackTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carBackTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carBackTex.setSmooth(true);

    filename = "carTopFront.png";
    if (!this->carTopFrontTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carTopFrontTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carTopFrontTex.setSmooth(true);

    filename = "carTopBack.png";
    if (!this->carTopBackTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carTopBackTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carTopBackTex.setSmooth(true);

    filename = "carTop.png";
    if (!this->carTopTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carTopTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carTopTex.setSmooth(true);

    filename = "window.png";
    if (!this->carWindowTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carWindowTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carWindowTex.setSmooth(true);

    filename = "carTail.png";
    if (!this->carTailTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carTailTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carTailTex.setSmooth(true);

    filename = "numberCar.png";
    if (!this->carNumberTex.loadFromFile(filename))
        throw "Erro: Falha ao carregar textura " + filename;
    if (!this->carNumberTex.generateMipmap())
        throw "Erro: Falha ao gerar mipmap da textura " + filename;
    this->carNumberTex.setSmooth(true);
}

sf::Texture *Textures::getTextureAddress(int type)
{
    switch (type)
    {
    case (TEX_CAR):
        return &this->carTex;
    case (TEX_TRAIN):
        return &this->trainTex;
    case (TEX_RAILWAY):
        return &this->railwayTex;
    case (TEX_FLOOR):
        return &this->floorTex;
    case (TEX_WALL):
        return &this->wallTex;
    case (TEX_WALL2):
        return &this->wall2Tex;
    case (TEX_WHEEL):
        return &this->wheelTex;
    case (TEX_WHEELCOLOR):
        return &this->wheelColorTex;
    case (TEX_CARFRONT):
        return &this->carFrontTex;
    case (TEX_CARBACK):
        return &this->carBackTex;
    case (TEX_CARTOPFRONT):
        return &this->carTopFrontTex;
    case (TEX_CARTOPBACK):
        return &this->carTopBackTex;
    case (TEX_CARTOP):
        return &this->carTopTex;
    case (TEX_CARWINDOW):
        return &this->carWindowTex;
    case (TEX_CARTAIL):
        return &this->carTailTex;
    case (TEX_CARNUMBER):
        return &this->carNumberTex;
    default:
        return NULL;
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