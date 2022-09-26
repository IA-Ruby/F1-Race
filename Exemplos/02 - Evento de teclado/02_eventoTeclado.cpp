#include <GL/glut.h>

/*
 * Programa básico para testar eventos de teclado na GLUT.
 * Um quadrado será desenhado.
 * O quadrado pode ser movido utilizando as teclas das setas
 * O quadrado pode mudar sua cor utilizando as teclas R (vermelho), G (verde) e B (azul)
 */

//Variáveis globais
float posx = -0.25; //coordenada x do vértice inferior esquerdo
float posy = -0.25; //coordenada y do vértice inferior esquerdo
float w =  0.50;    //largura do quadrado
float h =  0.50;    //altura do quadrado
float r =  1.0;     //componente vermelha da cor do quadrado
float g =  0.0;     //componente verde da cor do quadrado
float b =  0.0;     //componente azul da cor do quadrado


//É uma boa prática criar uma função para agrupar configurações iniciais do OpenGL para o desenho a ser feito
void inicio(){
    glClearColor(0.0, 0.0, 0.0, 1.0); //indica qual cor será usada para limpar o frame buffer (normalmente usa uma cor de background)
}

//Função indicada pra GLUT que será executada sempre que um evento de teclado que gere um caractere ASCII é criado
void tecladoASCII(unsigned char key, int x, int y){
    switch(key){ //nesse tipo de evento, a tecla pressionada é um caractere e pode ser acessada na instrução switch
        case 'r': 
        case 'R': r = 1 - r; break; //caso a tecla R seja pressionada, a componente vermelha é ligada ou desligada
        case 'g': 
        case 'G': g = 1 - g; break; //caso a tecla G seja pressionada, a componente verde é ligada ou desligada
        case 'b': 
        case 'B': b = 1 - b; break; //caso a tecla B seja pressionada, a componente azul é ligada ou desligada
    }
    
    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado
}

//Função indicada pra GLUT que será executada sempre que um evento de teclado a partir de uma tecla especial é criado
void tecladoSpecial(int key, int x, int y){
    switch(key){                                  //os códigos das teclas especiais são valores inteiros, então podem ser usados no switch
        case GLUT_KEY_LEFT:  posx -= 0.05; break; //caso a seta esquerda seja pressionada, a coordenada x do ponto inferior esquerdo é reduzida, deslocando o quadrado pra esquerda
        case GLUT_KEY_RIGHT: posx += 0.05; break; //caso a seta direita seja pressionada, a coordenada x do ponto inferior esquerdo é aumentada, deslocando o quadrado pra direita
        case GLUT_KEY_DOWN:  posy -= 0.05; break; //caso a seta pra baixo seja pressionada, a coordenada y do ponto inferior esquerdo é reduzida, deslocando o quadrado pra baixo
        case GLUT_KEY_UP:    posy += 0.05; break; //caso a seta pra cima seja pressionada, a coordenada y do ponto inferior esquerdo é aumentada, deslocando o quadrado pra cima
    }
    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado
}

//Função indicada na 'main' que será usada para redesenhar o conteúdo do frame buffer
void desenha(){
    glClear(GL_COLOR_BUFFER_BIT); 
    
    glColor3f(r, g, b);             //cor sendo definida pelas variáveis globais 'r', 'g' e 'b' 
    glBegin(GL_QUADS);              //instrução que indica que tipo de primitiva será desenhada. Nesse caso, quadriláteros.
        glVertex2f(posx  , posy  ); //alterando posx e posy, os vértices do quadrado mudam de lugar, ocasionando na mudança de sua posição. 
        glVertex2f(posx+w, posy  ); //apesar de funcionar aqui, há formas melhores de fazer um objeto se mover 
        glVertex2f(posx+w, posy+h);
        glVertex2f(posx  , posy+h);
    glEnd();
    
    glFlush();  
}

int main(int argc, char** argv){
    glutInit(&argc,argv);                         
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowPosition(200,200);              
    glutInitWindowSize(700,700);                  
    glutCreateWindow("Evento de teclado");        
 
    inicio();
 
    glutDisplayFunc(desenha);        //indica que a função 'desenha' deve ser chamada sempre que o frame buffer deve ser atualizado
    glutKeyboardFunc(tecladoASCII);  //indica que a função 'tecladoASCII' deve ser chamada sempre que uma tecla gere um caractere ASCII é pressionada
    glutSpecialFunc(tecladoSpecial); //indica que a função 'tecladoSpecial' deve ser chamada sempre que uma tecla especial é pressionada (Esc, Ctrl, Setas do teclado, Enter, etc.)
 
    glutMainLoop(); //mantém um laço interno para que a janela permaneça aberta
    
    return 0;
}
