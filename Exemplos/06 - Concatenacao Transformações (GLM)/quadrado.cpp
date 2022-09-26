#include "quadrado.h"

#include <GL/gl.h>

Quadrado::Quadrado(float lado, glm::vec3 cor){
    this->lado = lado;
    this->cor = cor;
}

void Quadrado::desenha(){
    glColor3f(cor.r, cor.g, cor.b);
    glBegin(GL_QUADS);
        glVertex2f(-lado/2, -lado/2);
        glVertex2f( lado/2, -lado/2);
        glVertex2f( lado/2,  lado/2);
        glVertex2f(-lado/2,  lado/2);
    glEnd();
}
