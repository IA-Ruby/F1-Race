#include <SFML/glut.h>

/*
 * Programa 'Olá mundo' de OpenGL clássico.
 * Desenha um triângulo vermelho sobre um fundo branco.
 */


//É uma boa prática criar uma função para agrupar configurações iniciais do OpenGL para o desenho a ser feito
void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor será usada para limpar o frame buffer (normalmente usa uma cor de background)
}


//Função indicada na 'main' que será usada para redesenhar o conteúdo do frame buffer
void desenha(){
    glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o frame-buffer
    
    glColor3f(1.0, 0.0, 0.0);    //instrução que altera a cor corrente. Entrada em RGB. Nesse caso, vermelho
    glBegin(GL_TRIANGLES);       //instrução que indica que tipo de primitiva será desenhada. Nesse caso, triângulos.
        glVertex2f(-0.5, -0.5);  //instrução que envia as coordenadas dos vértices do triângulo
        glVertex2f( 0.5, -0.5);  
        glVertex2f( 0.0,  0.5);
    glEnd();
    
    glFlush();  //Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv){
    glutInit(&argc,argv);                         //inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //configurações do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(200,200);              //posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(700,700);                  //resolução da janela (framebuffer)
    glutCreateWindow("Janela Teste");             //cria a janela (a string aparece na barra de título da janela)
 
    inicio();
 
    glutDisplayFunc(desenha);   //indica que a função 'desenha' deve ser chamada sempre que o frame buffer deve ser atualizado
 
    glutMainLoop();             //mantém um laço interno para que a janela permaneça aberta
    
    return 0;
}
