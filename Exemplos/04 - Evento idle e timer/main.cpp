#include <GL/glut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "objeto.h"

#define FPS 60

using namespace std;

/*
 * Programa básico para realizar animações na GLUT.
 * O programa desenha um relógio circular com três ponteiros: horas, minutos e segundos
 * Foram usadas duas formas de controlar a execução da atualização do relógio: controlando o tempo e executando continuamente
 * Para usar uma ou a outra, comente uma das chamadas na função 'main'
 */

//Variáveis globais
Objeto A(glm::vec2(0,3) ,DIREITA,glm::vec3(1,0,0));
Objeto B(glm::vec2(0,-3),DIREITA,glm::vec3(0,0,1));

//Função com configurações iniciais da aplicação
void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPointSize(30.0); //pontos terão uma largura de aproximadamente 10 pixels
    glLineWidth(3.0);  //segmentos de reta terão uma largura de aproximadamente 3 pixels
    glEnable(GL_MULTISAMPLE); //habilita um tipo de antialiasing
}

//Função indicada pra GLUT que será executada após uma certa quantidade de tempo
void timer(int v){
    //A função glutTimerFunc indica pra GLUT que a função 'timer' irá executar daqui a uma certa quantidade de milissegundos. No exemplo: 1000 milissegundos = 1 segundo
    //Desejamos que essa função seja executada novamente daqui a um segundo. Por isso, precisa ser colocada essa instrução aqui.
    //Atenção! Não chame timer dentro de timer. Isso criará uma recursão infinita.
    glutTimerFunc(1000.0/FPS, timer, 0);

    A.move(0.1);
    B.move(0.2);

    glutPostRedisplay();
}

//Função indicada pra GLUT que será executada o tempo inteiro
void idle(){
    //A função glutIdleFunc indica pra GLUT que a função 'idle' será executada o tempo inteiro, sem intervalo de tempo entre uma chamada e a próxima.
    //A velocidade das chamadas depende do poder de processamento do computador.
    //Quanto maior o poder de processamento do computador, mais chamadas são feitas à função.


    glutPostRedisplay();
}

//Função indicada na 'main' que será usada para redesenhar o conteúdo do frame buffer
void desenha(){
    //limpa frame buffer
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10,10,-1,1);

    glMatrixMode(GL_MODELVIEW); //habilita transformações geométricas como a rotação
    glLoadIdentity();           //inicializa essas transformações com uma transformação neutra (que não altera nada)

    A.desenha();
    B.desenha();

    glutSwapBuffers();  //Em animações, é útil utilizar dois frame-buffers trabalhando em paralelo. Essa instrução troca um buffer pelo outro.
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    //GLUT_DOUBLE define que utilizará dois frame-buffers. Isso é útil em animações para evitar o problema de 'flickering' (pisca-pisca)
    //GLUT_MULTISAMPLE define que vários pontos dentro de um mesmo pixel serão calculados para realizar o antialiasing (serrilhado nas bordas)
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(700,700);
    glutCreateWindow("Evento de timer");

    inicio();

    glutDisplayFunc(desenha);

    //Há duas formas de implementar um timer:
    //- um timer com espera (glutTimerFunc)
    //- um timer sem espera (glutIdleFunc)
    //Escolha qual das duas deseja ativar abaixo:
    glutTimerFunc(1000.0/FPS, timer, 0);
    //glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
