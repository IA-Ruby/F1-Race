#include "../header/field.h"
#include <GL/gl.h>

Field::Field(GLubyte colorField[3], GLubyte colorBG[3]){
    for(int i=0; i<3; i++){
        this->colorField[i] = colorField[i]; 
        this->colorBG[i] = colorBG[i];
    }
    initQueues();
}

void Field::draw(float speed){
    updField(speed);
    drawMode(GL_LINE,colorField);
    drawMode(GL_FILL,colorBG);
    drawTrees();
}

void Field::drawMode(int mode, GLubyte color[3]){
    //Alternancia entre preenchimento e contorno
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    //Desenha o campo e as montanhas
    for(int i=-1; i<=1; i+=2){
        glPushMatrix();
            glTranslatef(83*i,0,-6.f);
            glColor3ubv(color);
            for(int j=0; j<(cordY.size()-1); j++){
                glBegin(GL_QUAD_STRIP);
                for(int k=0; k<34; k++){
                    if(k>=20){
                        glVertex3f( k*20*i, cordY[j],   cordZRight[j][k-20]);
                        glVertex3f( k*20*i, cordY[j+1], cordZRight[j+1][k-20]); 
                    }else{
                        glVertex3f( k*20*i, cordY[j],   0);
                        glVertex3f( k*20*i, cordY[j+1], 0);
                    }
                }
                glEnd();
            }
        glPopMatrix();
    }
}

void Field::drawTrees(){
    // Desenha as arvores
    for(int i=0; i<treesLeft.size(); i++){
        glPushMatrix();
            glTranslatef(-200,treesLeft[i].getCordTree(), -5.8);
            treesLeft[i].draw();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(200,treesRight[i].getCordTree(), -5.8);
            glRotatef(180,0,0,1);
            treesRight[i].draw();
        glPopMatrix();
    }
}

// Função para atualizar as variaveis com base na velocidade
void Field::updField(float speed){
    // Atualiza as coordenadas das linhas
    for(int i=0; i<cordY.size(); i++){
        cordY[i] -= speed;
        if(cordY[i]<-400.f){
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
            treesRight.push_back( Tree(colorBG, (treesRight.back().getCordTree()+2000+rand()%1000-500)));
            i--; 
        }
    }
    for(int i=0; i<treesLeft.size(); i++){
        treesLeft[i].setCordTree(treesLeft[i].getCordTree() - speed);
        if(treesLeft[i].getCordTree() < -200.f){
            treesLeft.pop_front();
            treesLeft.push_back( Tree(colorBG, (treesLeft.back().getCordTree()+2000+rand()%1000-500)));
            i--;
        }
    }
}

// Função para iniciar todas as filas;
void Field::initQueues(){
    for(int i=0; i<=100; i++){
        cordZRight.push_back(randMountain());
        cordZLeft.push_back(randMountain());
        cordY.push_back(i*200);
    }

    treesRight.push_back(Tree(colorBG, 2000+rand()%1000-500));
    for(int i = 0; treesRight.back().getCordTree() < 18000; i++)
        treesRight.push_back( Tree(colorBG, (treesRight[i].getCordTree()+2000+(rand()%1000-500))));        

    treesLeft.push_back(Tree(colorBG, 2000+rand()%1000-500));
    for(int i = 0; treesLeft.back().getCordTree() < 18000; i++)
        treesLeft.push_back( Tree(colorBG, (treesLeft[i].getCordTree()+2000+(rand()%1000-500))));        
}

// Função para gerar deformidade das montanhas
vector<int> Field::randMountain(){
    vector<int> aux;
    for(int j=0; j<15; j++){
        if(j == 0) aux.push_back(rand()%10);    
        if(j == 1) aux.push_back(rand()%30+10);
        if(j == 2) aux.push_back(rand()%60+30);
        if(j == 3) aux.push_back(rand()%80+60);
        if(j == 4) aux.push_back(rand()%100+80);
        if(j == 5) aux.push_back(rand()%120+100);
        if(j == 6) aux.push_back(rand()%130+120);
        if(j == 7) aux.push_back(rand()%140+130);
        if(j == 8) aux.push_back(rand()%150+140);
        if(j >= 9) aux.push_back(rand()%155+150);
    }
    return aux;
}