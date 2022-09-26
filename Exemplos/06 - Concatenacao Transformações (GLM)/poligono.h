#ifndef POLIGONO_H
#define POLIGONO_H

#include <glm/glm.hpp>

class Poligono{
    private:
        int       nLados;
        float     raio;
        glm::vec3 cor;
    public:
        Poligono(int nLados, float raio, glm::vec3 cor);
        void desenha();
};

#endif // POLIGONO_H
