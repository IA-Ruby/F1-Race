#ifndef QUADRADO_H
#define QUADRADO_H

#include <glm/glm.hpp>

class Quadrado{
    private:
        float lado;
        glm::vec3 cor;
    public:
        Quadrado(float lado, glm::vec3 cor);
        void desenha();
};

#endif // QUADRADO_H
