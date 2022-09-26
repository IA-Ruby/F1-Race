#include "objeto.h"

#include <GL/gl.h>

Objeto::Objeto(glm::vec2 posicao, int direcao, glm::vec3 cor){
    this->posicao = posicao;
    this->direcao = direcao;
    this->cor = cor;
}

void Objeto::move(float distancia){
    if(direcao == DIREITA){
        posicao.x += distancia;
        if(posicao.x > 10) direcao = ESQUERDA;
    }
    else{
        posicao.x -= distancia;
        if(posicao.x < -10) direcao = DIREITA;
    }
}

void Objeto::desenha(){
    glColor3f(cor.r,cor.g,cor.b);
    glBegin(GL_POINTS);
        glVertex2f(posicao.x, posicao.y);
    glEnd();
}
