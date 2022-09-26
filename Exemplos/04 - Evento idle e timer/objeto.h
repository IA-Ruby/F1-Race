#ifndef OBJETO_H
#define OBJETO_H

#include <glm/glm.hpp>

enum{
    ESQUERDA = 1,
    DIREITA
};

class Objeto{
    private:
        glm::vec2 posicao;
        int       direcao;
        glm::vec3 cor;
    public:
        Objeto(glm::vec2 posicao, int direcao, glm::vec3 cor);
        void move(float distancia);
        void desenha();
};

#endif // OBJETO_H
