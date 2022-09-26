#include <GL/glut.h>

/*
 * Programa 'Primitivas' de OpenGL clássico.
 * Desenha diversas primitivas geométricas presentes em OpenGL
 */

//É uma boa prática criar uma função para agrupar configurações iniciais do OpenGL para o desenho a ser feito
void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor será usada para limpar o frame buffer (normalmente usa uma cor de background)
    glPointSize(5); //altera o tamanho de pontos (por padrão, o tamanho é de 1 pixel)
    glLineWidth(3); //altera a largura de segmentos de reta (por padrão, a largura é de 1 pixel)
}

//função que desenha várias primitivas diferentes para exemplificar seu uso
void primitivas(){
    glBegin(GL_POINTS); //pontos
        glVertex2f( 1, 1);
        glVertex2f( 4, 1);
        glVertex2f( 4, 4);
        glVertex2f( 1, 4);
    glEnd();
    
    glBegin(GL_LINES); //a cada dois pontos, conecte-os em segmentos de reta
        glVertex2f( 5, 1);
        glVertex2f( 8, 1);
        glVertex2f( 8, 4);
        glVertex2f( 5, 4);
    glEnd();
    
    glBegin(GL_LINE_STRIP); //conecte uma sequência de pontos em segmentos de reta
        glVertex2f( 9, 1);
        glVertex2f(12, 1);
        glVertex2f(12, 4);
        glVertex2f( 9, 4);
    glEnd();
    
    glBegin(GL_LINE_LOOP); //conecte uma sequência de pontos em segmentos de reta e o último ponto com o primeiro
        glVertex2f(13, 1);
        glVertex2f(16, 1);
        glVertex2f(16, 4);
        glVertex2f(13, 4);
    glEnd();
    
    glBegin(GL_QUADS); //a cada quatro pontos, conecte-os em quadriláteros
        glVertex2f( 1, 5);
        glVertex2f( 4, 5);
        glVertex2f( 4, 8);
        glVertex2f( 1, 8);
    glEnd();
    
    glBegin(GL_TRIANGLES); //a cada três pontos, conecte-os em triângulos
        glVertex2f( 5, 5);
        glVertex2f( 8, 5);
        glVertex2f( 5, 8);
        glVertex2f( 5, 8);
        glVertex2f( 8, 5);
        glVertex2f( 8, 8);
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP); //cada novo ponto é conectado aos dois últimos formando triângulos
        glVertex2f( 9, 5);
        glVertex2f( 9, 8);
        glVertex2f(10, 5);
        glVertex2f(10, 8);
        glVertex2f(11, 5);
        glVertex2f(11, 8);
        glVertex2f(12, 5);
        glVertex2f(12, 8);
    glEnd();
    
    glBegin(GL_QUAD_STRIP); //cada dois novos pontos são conectados aos dois últimos formando quadriláteros
        glVertex2f(13, 5);
        glVertex2f(13, 8);
        glVertex2f(14, 5);
        glVertex2f(14, 8);
        glVertex2f(15, 5);
        glVertex2f(15, 8);
        glVertex2f(16, 5);
        glVertex2f(16, 8);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN); //o primeiro ponto é conectado a todos os demais formando triângulos
        glVertex2f(2.5,10.5);
        glVertex2f(  1,  9);
        glVertex2f(  4,  9);
        glVertex2f(  4, 12);
        glVertex2f(  1, 12);
        glVertex2f(  1,  9);
    glEnd();
    
    glBegin(GL_POLYGON); //polígono de vários lados (deve ser evitado)
        glVertex2f( 5,10);
        glVertex2f( 6, 9);
        glVertex2f( 7, 9);
        glVertex2f( 8,10);
        glVertex2f( 8,11);
        glVertex2f( 7,12);
        glVertex2f( 6,12);
        glVertex2f( 5,11);
    glEnd();
    
    glBegin(GL_QUADS); //quadriláteros e polígonos com a ordem dos vértices incorreta pode levar a esse tipo de erro
        glVertex2f( 9, 9);
        glVertex2f(12, 9);
        glVertex2f( 9,12);
        glVertex2f(12,12);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN); //GL_POLYGON pode ser substituído por GL_TRIANGLE_FAN
        glVertex2f(13,10);
        glVertex2f(14, 9);
        glVertex2f(15, 9);
        glVertex2f(16,10);
        glVertex2f(16,11);
        glVertex2f(15,12);
        glVertex2f(14,12);
        glVertex2f(13,11);
    glEnd();
}

//Função indicada na 'main' que será usada para redesenhar o conteúdo do frame buffer
void desenha(){
    glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o frame-buffer

    //comandos que determinam a visualização da cena (explicado em mais detalhes futuramente)
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glOrtho(0,17,0,17,-1,1); //glOrtho(xmin,xmax,ymin,ymax,zmin,zmax) = alterando a área de visualização
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); //alterando para modo de preenchimento (por padrão já vem ativado)
    glColor3f(1.0, 0.0, 0.0);  //cor de preenchimento vermelha  
    primitivas();

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); //alterando para modo de linhas (usado para mostrar as arestas dos polígonos)
    glColor3f(0.0, 0.0, 0.0);  //cor das linhas pretas
    primitivas();

    glFlush(); //Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv){
    glutInit(&argc,argv);                        //inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //configurações do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(0,0);                 //posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(500,500);                 //resolução da janela (framebuffer)
    glutCreateWindow("01 - Primitivas");         //cria a janela (a string aparece na barra de título da janela)

    inicio();

    glutDisplayFunc(desenha); //indica que a função 'desenha' deve ser chamada sempre que o frame buffer deve ser atualizado

    glutMainLoop();           //mantém um laço interno para que a janela permaneça aberta

    return 0;
}
