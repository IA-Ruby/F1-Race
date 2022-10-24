#include "../header/field.h"
#include <GL/gl.h>

Field::Field(GLubyte colorField[3], GLubyte colorBG[3], GLubyte colorLeaves[3], GLubyte colorWood[3]){
    for(int i=0; i<3; i++){
        this->colorField[i] = colorField[i]; 
        this->colorBG[i] = colorBG[i];
        this->colorLeaves[i] = colorLeaves[i];
        this->colorWood[i] = colorWood[i];
    }
    initQueues();
}

void Field::draw(float speed, bool show){
    updField(speed);
    drawMode(GL_LINE,colorField, show);
    drawMode(GL_FILL,colorBG, show);
}

void Field::drawMode(int mode, GLubyte color[3], bool show){
    //Alternancia entre preenchimento e contorno
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    //Desenha o campo e as montanhas
    glPushMatrix();
        glTranslatef(83,0,-6.f);
        glColor3ubv(color);
        for(int i=0; i<(cordY.size()-1); i++){
            glBegin(GL_QUAD_STRIP);
            for(int j=0; j<29; j++){
                if(j>=20){
                    glVertex3f( j*20, cordY[i],   cordZRight[i][j-20]);
                    glVertex3f( j*20, cordY[i+1], cordZRight[i+1][j-20]); 
                }else{
                    glVertex3f( j*20, cordY[i],   1);
                    glVertex3f( j*20, cordY[i+1], 1);
                }
            }
            glEnd();
        }
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-83,0,-6.f);
        glColor3ubv(color);
        for(int i=0; i<(cordY.size()-1); i++){
            glBegin(GL_QUAD_STRIP);
            for(int j=0; j<29; j++){
                if(j>=20){
                    glVertex3f(-j*20, cordY[i],   cordZLeft[i][j-20]); 
                    glVertex3f(-j*20, cordY[i+1], cordZLeft[i+1][j-20]); 
                }else{
                    glVertex3f(-j*20, cordY[i],   1);
                    glVertex3f(-j*20, cordY[i+1], 1);
                }
            }
            glEnd();
        }
    glPopMatrix();
    
    // Desenha as arvores
    for(int i=0; i<treesLeft.size(); i++){
        glPushMatrix();
            glTranslatef(-200,treesLeft[i].getCordTree(), -5.8);
            treesLeft[i].draw(show);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(200,treesRight[i].getCordTree(), -5.8);
            glRotatef(180,0,0,1);
            treesRight[i].draw(show);
        glPopMatrix();
    }
}

// Função para atualizar as variaveis com base na velocidade
void Field::updField(float speed){
    // Atualiza as coordenadas das linhas
    for(int i=0; i<cordY.size(); i++){
        cordY[i] -= speed;
        if(cordY[i]<-200.f){
            cordY.push_back(cordY[i] + (cordY.size()*200));
            cordY.pop_front();
            i--;
            cordZRight.pop_front();
            cordZLeft.pop_front();
            cordZRight.push_back(randMountain());
            cordZLeft.push_back(randMountain());
        }
    }

    // Atualiza as coordenadas as colunas (montanhas)
    for(int i=0; i<treesRight.size(); i++){
        treesRight[i].setCordTree(treesRight[i].getCordTree() - speed);
        if(treesRight[i].getCordTree() < -200.f){
            treesRight.pop_front();
            treesRight.push_back(Tree(  colorLeaves, 
                                        colorWood, 
                                        colorBG, 
                                        (treesRight.back().getCordTree()+2000+rand()%1000-500)));
            i--; 
        }
    }
    for(int i=0; i<treesLeft.size(); i++){
        treesLeft[i].setCordTree(treesLeft[i].getCordTree() - speed);
        if(treesLeft[i].getCordTree() < -200.f){
            treesLeft.pop_front();
            treesLeft.push_back(Tree(  colorLeaves, 
                                        colorWood, 
                                        colorBG, 
                                        (treesLeft.back().getCordTree()+2000+rand()%1000-500)));
            i--;
        }
    }
}

// Função para iniciar todas as filas;
void Field::initQueues(){
    for(int i=0; i<101; i++){
        cordZRight.push_back(randMountain());
        cordZLeft.push_back(randMountain());
        cordY.push_back(i*200);
    }

    treesRight.push_back(Tree(colorLeaves, colorWood, colorBG, 2000+rand()%1000-500));
    for(int i = 0; treesRight.back().getCordTree() < 18000; i++){
        treesRight.push_back(Tree(  colorLeaves, 
                                    colorWood, 
                                    colorBG, 
                                    (treesRight[i].getCordTree()+2000+(rand()%1000-500))));        
    }

    treesLeft.push_back(Tree(colorLeaves, colorWood, colorBG, 2000+rand()%1000-500));
    for(int i = 0; treesLeft.back().getCordTree() < 18000; i++){
        treesLeft.push_back(Tree(   colorLeaves, 
                                    colorWood, 
                                    colorBG, 
                                    (treesLeft[i].getCordTree()+2000+(rand()%1000-500))));        
    }
}

// Função para gerar deformidade das montanhas
vector<int> Field::randMountain(){
    vector<int> aux;
    for(int j=0; j<10; j++){
        if(j == 0){
            aux.push_back(rand()%10);    
        }else if(j==1){
            aux.push_back(rand()%30+10);
        }else if(j==2){
            aux.push_back(rand()%60+30);
        }else if(j==3){
            aux.push_back(rand()%80+60);
        }else if(j==4){
            aux.push_back(rand()%100+80);
        }else if(j==5){
            aux.push_back(rand()%120+100);
        }else if(j==6){
            aux.push_back(rand()%130+120);
        }else if(j==7){
            aux.push_back(rand()%140+130);
        }else if(j==8){
            aux.push_back(rand()%150+140);
        }else if(j==9){
            aux.push_back(rand()%155+150);
        }
    }
    return aux;
}