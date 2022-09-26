#include "poligono.h"

#include <cmath>
#include <GL/gl.h>

Poligono::Poligono(int nLados, float raio, glm::vec3 cor){
    this->nLados = nLados;
    this->raio   = raio;
    this->cor    = cor;
}

void Poligono::desenha(){
    glColor3f(cor.r, cor.g, cor.b);
    glBegin(GL_POLYGON);
        for(int i = 0 ; i < nLados ; i++){
            float ang = i * (2.0*M_PI/nLados);
            float x = raio * cos(ang);
            float y = raio * sin(ang);
            glVertex2f(x,y);
        }
    glEnd();
}
