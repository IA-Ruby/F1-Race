#include <GL/glut.h>
#include <glm/glm.hpp>
#include <cmath>

using namespace std;

/*
 * Programa básico para mostrar transformações de translação, rotação e escala feitas usando OpenGL clássico
 * O programa desenha:
 * - um hexágono vermelho sendo transformado por uma rotação
 * - dois retângulos verdes sendo transformados por translações
 * - um quadrado azul sendo transformado por uma escala não-uniforme
 */

//Variáveis globais
int   angRotacao = 0;                                      //ângulo que controlará a rotação do hexágono vermelho
glm::vec2 translacaoRet1(0,0.75), translacaoRet2(0,-0.75); //vetores de translação dos retângulos verdes
glm::vec2 escalaQuad(1,1);                                 //fatores de escala do quadrado azul
float variacaoTranslacao = 0.02;                           //mudança da posição a cada frame
float variacaoEscala = 0.02;                               //mudança da escala a cada frame

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
    angRotacao++;
    if(angRotacao >= 360) angRotacao = 0;

    //atualizando o vetor de translação a cada frame
    //a posição do retangulo 1 soma e a do retangulo 2 subtrai para irem em direções opostas
    translacaoRet1.x += variacaoTranslacao;
    translacaoRet2.x -= variacaoTranslacao;
    //se a posição do retângulo 1 alcanca as bordas, muda o sinal da variação para mudar a direção
    if(translacaoRet1.x > 0.75 || translacaoRet1.x < -0.75) variacaoTranslacao = -variacaoTranslacao;

    //atualizando os fatores de escala a cada frame
    //a escala do quadrado no eixo x aumenta enquanto a do y diminui
    escalaQuad.x += variacaoEscala;
    escalaQuad.y -= variacaoEscala;
    //quando a escala atingir um valor limite, a variação muda de sinal para fazer o inverso de antes
    if(escalaQuad.x > 1.5 || escalaQuad.x < 0.5) variacaoEscala = -variacaoEscala;

    glutPostRedisplay();
}

//Função indicada na 'main' que será usada para redesenhar o conteúdo do frame buffer
void desenha(){
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); //habilita o uso de matrizes de transformações geométricas
    glLoadIdentity();           //inicializa a matriz de trasnformação com a matriz identidade (não altera as coordenadas dos pontos)

    glPushMatrix();                 //salvando a matriz de transformação atual
    glRotatef(angRotacao, 0,0,1);   //aplicando a matriz de rotação (o vetor (0,0,1) em uma aplicação 2D é o eixo saindo da tela)
    glColor3f(1,0,0);
    circulo(0.5, 6);                //um "círculo" de 6 lados é um hexágono regular
    glPopMatrix();                  //recarregando a matriz de transformação antes da rotação (isso fará com que a rotação aplicada no hexágono não afete os demais objetos)

    glPushMatrix();
    glTranslatef(translacaoRet1.x,translacaoRet1.y,0); //aplicando a matriz de translação (a coordenada z é igual a zero em aplicações 2D)
    glColor3f(0,1,0);
    retangulo(0.3, 0.1);                               //desenhando o primeiro retângulo verde de lado 0.3 e altura 0.1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(translacaoRet2.x,translacaoRet2.y,0); //aplicando a matriz de translação (a coordenada z é igual a zero em aplicações 2D)
    glColor3f(0,0.5,0);
    retangulo(0.3, 0.1);                               //desenhando o segundo retângulo verde de lado 0.3 e altura 0.1
    glPopMatrix();

    glPushMatrix();
    glScalef(escalaQuad.x,escalaQuad.y,1); //aplicando a matriz de escala (a coordenada z é igual a 1, porque escala multiplica os fatores e a multiplicação é o elemento neutro da multiplicação)
    glColor3f(0,0,1);
    retangulo(0.3, 0.3);         //desenhando um quadrado azul de lado 0.3 centrado na orgem
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(700,700);
    glutCreateWindow("Transformacoes Geometricas 2D - OpenGL Classico");

    inicio();

    glutDisplayFunc(desenha);
    glutTimerFunc(1000.0/30, timer, 0);

    glutMainLoop();

    return 0;
}
