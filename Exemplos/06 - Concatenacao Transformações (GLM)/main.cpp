#include <GL/glut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "poligono.h"
#include "quadrado.h"

/*
 * Programa básico para mostrar concatenação de transformações geométricas usando OpenGL clássico
 * O programa desenha dois hexágonos vermelhos e dois retângulos verdes
 * O hexágono vermelho claro é transformado primeiro pela rotação e depois pela translação
 * O hexágono vermelho escuro é transformado primeiro pela translação e depois pela rotação
 * O retângulo verde claro é transformado primeiro pela escala e depois pela rotação (no final, é transladado para não ficar por cima do outro retângulo)
 * O retângulo verde escuro é transformado primeiro pela rotação e depois pela escala (no final, é transladado para não ficar por cima do outro retângulo)
 * O comando glMultMatrixf() substitui todas as operações de transformações anteriores
 * O comango glm::value_ptr() converte o tipo glm::mat4 em um vetor float
 */

//Variáveis globais
float angRotacao = 0; //ângulo que controlará a rotação do hexágono vermelho
Poligono hexagono1(6,0.15,glm::vec3(  1,0,0));
Poligono hexagono2(6,0.15,glm::vec3(0.5,0,0));
Quadrado quadrado1(0.3, glm::vec3(0,  1,0));
Quadrado quadrado2(0.3, glm::vec3(0,0.5,0));

//Função que desenha um "círculo" centrado na origem (aqui, irei desenhar um "círculo" com 6 lados, o que vai aparentar um hexágono na tela)
void circulo(float raio, int divisioes){
    glBegin(GL_POLYGON);
        for(int i = 0 ; i < divisioes ; i++){
            float ang = i * (2.0*M_PI/divisioes);
            float x = raio * cos(ang);
            float y = raio * sin(ang);
            glVertex2f(x,y);
        }
    glEnd();
}

//Função que desenha um retângulo centrado na origem
void retangulo(float largura, float altura){
    glBegin(GL_QUADS);
        glVertex2f(-largura/2, -altura/2);
        glVertex2f( largura/2, -altura/2);
        glVertex2f( largura/2,  altura/2);
        glVertex2f(-largura/2,  altura/2);
    glEnd();
}

//Função com configurações iniciais da aplicação
void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

//Função indicada pra GLUT que será executada após uma certa quantidade de tempo
void timer(int v){
    glutTimerFunc(1000.0/30, timer, 0); //Controlando o desenho a cada 1000/30 significa que a tela será redesenhada 30 frames por segundo

    //atualizando o ângulo de rotação a cada frame
    angRotacao += 1.0f;
    if(angRotacao >= 360.0) angRotacao -= 360.0;

    glutPostRedisplay();
}

//Função indicada na 'main' que será usada para redesenhar o conteúdo do frame buffer
void desenha(){
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); //habilita o uso de matrizes de transformações geométricas
    glLoadIdentity();           //inicializa a matriz de trasnformação com a matriz identidade (não altera as coordenadas dos pontos)

    //OpenGL obedece a ordem da multiplicação de matrizes (ordem inversa das transformações)
    glm::mat4 I = glm::mat4(1.0f); //matriz identidade
    glm::mat4 T1 = glm::translate(I,glm::vec3(0.5,0.5,0.0));  //translação aplicada nos hexágonos
    glm::mat4 T2 = glm::translate(I,glm::vec3(0.3,0.0,0.0));  //translação aplicada no quadrado 1
    glm::mat4 T3 = glm::translate(I,glm::vec3(-0.3,0.0,0.0)); //translação aplicada no quadrado 2
    glm::mat4 R = glm::rotate(I,glm::radians(angRotacao),glm::vec3(0,0,1)); //rotação aplicada a todos
    glm::mat4 S = glm::scale(I,glm::vec3(1.5,0.5,1.0));                     //escala aplicada nos quadrados
    glm::mat4 M; //matriz resultado da concatenação das transformações

    glPushMatrix();
    M = T1 * R; //ordem: rotação -> translação
    glMultMatrixf( glm::value_ptr(M) );
    hexagono1.desenha();
    glPopMatrix();

    glPushMatrix();
    M = R * T1; //ordem translação -> rotação (efeito colateral de rotação de objeto fora da origem)
    glMultMatrixf( glm::value_ptr(M) );
    hexagono2.desenha();
    glPopMatrix();

    glPushMatrix();
    M = T2 * R * S; //ordem: escala -> rotação -> translação
    glMultMatrixf( glm::value_ptr(M) );
    quadrado1.desenha();
    glPopMatrix();

    glPushMatrix();
    M = T3 * S * R; //ordem: rotação -> escala -> translação
    glMultMatrixf( glm::value_ptr(M) );
    quadrado2.desenha();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(700,700);
    glutCreateWindow("Concatenacao de Transformacoes 2D - Biblioteca GLM");

    inicio();

    glutDisplayFunc(desenha);
    glutTimerFunc(1000.0/30, timer, 0); //Controlando o desenho a cada 1000/30 significa que a tela será redesenhada 30 frames por segundo

    glutMainLoop();

    return 0;
}
