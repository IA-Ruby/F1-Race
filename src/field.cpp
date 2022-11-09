#include "../header/field.h"
#include <GL/gl.h>

Field::Field(GLubyte colorField[3], GLubyte colorBG[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->colorField[i] = colorField[i];
        this->colorBG[i] = colorBG[i];
    }
    initQueues();
    // finish = false;
}

void Field::draw(float speed)
{
    updField(speed);
    drawMountains(GL_LINE, colorField);
    drawMountains(GL_FILL, colorBG);
    drawTrees();
    // if(finish)
    // {
    //     drawTunnel(GL_LINE, colorField);
    //     drawTunnel(GL_FILL, colorBG);
    // }
}

void Field::drawMountains(int mode, GLubyte color[3])
{
    // Alternancia entre preenchimento e contorno
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    // Desenha o campo e as montanhas
    for (int i = -1; i <= 1; i += 2)
    {
        glPushMatrix();
            glTranslatef(83 * i, 0, -6.7);
            glColor3ubv(color);
            for (int j = 0; j < (cordY.size() - 1); j++)
            {
                glBegin(GL_QUAD_STRIP);
                for (int k = 0; k < 30; k++)
                {
                    if(cordY[j] <= 14000)
                    {
                        glVertex3f(k * 20 * i,     cordY[j],     cordZRight[j][k]);
                        glVertex3f(k * 20 * i, cordY[j + 1], cordZRight[j + 1][k]);   
                    }    
                    else
                    {
                        glVertex3f(k * 20 * i,     cordY[j],     cordZRight[j][k] - (cordY[j]-14000)/100);
                        glVertex3f(k * 20 * i, cordY[j + 1], cordZRight[j + 1][k] - (cordY[j]-14000)/100);
                    }
                }
                glEnd();
            }
        glPopMatrix();
    }
}

// Desenha as arvores
void Field::drawTrees()
{
    for (int i = 0; i < treesLeft.size(); i++)
    {
        glPushMatrix();
            glTranslatef( treesLeft[i].getCordTree().x, treesLeft[i].getCordTree().y, treesLeft[i].getCordTree().z-6.7);
            treesLeft[i].draw();
        glPopMatrix();
    }
    
    for (int i = 0; i < treesRight.size(); i++)
    {    
        glPushMatrix();
            glTranslatef( treesRight[i].getCordTree().x, treesRight[i].getCordTree().y, treesRight[i].getCordTree().z-6.7);
            glRotatef(180, 0, 0, 1);
            treesRight[i].draw();
        glPopMatrix();
    }
}

// Desenha o tunnel
void drawTunnel(int mode, GLubyte color[3])
{
    glPushMatrix();
        glScalef(80,1,80);
        glColor3ubv(color);
        glBegin(GL_QUAD_STRIP);    
            for (float angulo = 0; angulo <= 180; angulo += 20){
                float x = cos(angulo*M_PI/180.0);
                float z = sin(angulo*M_PI/180.0);
                glVertex3f(x,0,z);
                glVertex3f(x,1,z);
            }
        glEnd();
    glPopMatrix();
}

// Função para atualizar as variaveis com base na velocidade
void Field::updField(float speed)
{
    // Atualiza as coordenadas das linhas e montanhas
    for (int i = 0; i < cordY.size(); i++)
    {
        cordY[i] -= speed;
 
        if (cordY[i] < -400.f)
        {
            cordY.push_back(cordY[i] + (cordY.size() * 200));
            cordY.pop_front();
            i--;
            cordZRight.pop_front();
            cordZLeft.pop_front();
            cordZRight.push_back(randMountain());
            cordZLeft.push_back(randMountain());
        }
    }

    // Atualiza as coordenadas das arvores
    for (int i = 0; i < treesRight.size(); i++)
    {
        treesRight[i].setCordYTree(treesRight[i].getCordTree().y - speed);
        if (treesRight[i].getCordTree().y < -200.f)
        {
            treesRight.pop_front();
            treesRight.push_back(Tree(colorBG, vec3(rand() % 100 + 200, 
                                                    treesRight.back().getCordTree().y + 2000 + (rand() % 1000 - 500),
                                                    0)));
            i--;
            if(treesRight.back().getCordTree().y > 14000)
            {
                treesRight.back().setCordZTree(-(treesRight.back().getCordTree().y-14000)/100);
            }
        }
        else
        {
            treesRight[i].setCordZTree(treesRight[i].getCordTree().z + speed/100);
            if(treesRight[i].getCordTree().z > 0){
                treesRight[i].setCordZTree(0);
            }
        }
    }

    for (int i = 0; i < treesLeft.size(); i++)
    {
        treesLeft[i].setCordYTree(treesLeft[i].getCordTree().y - speed);
        if (treesLeft[i].getCordTree().y < -200.f)
        {
            treesLeft.pop_front();
            treesLeft.push_back(Tree(colorBG, vec3((rand() % 100 + 200) * -1, 
                                                    treesLeft.back().getCordTree().y + 2000 + (rand() % 1000 - 500), 
                                                    0)));
            i--;
            if(treesLeft.back().getCordTree().y > 14000)
            {
                treesLeft.back().setCordZTree(-(treesLeft.back().getCordTree().y-14000)/100);
            }
        }
        else
        {
            treesLeft[i].setCordZTree(treesLeft[i].getCordTree().z + speed/100);
            if(treesLeft[i].getCordTree().z > 0){
                treesLeft[i].setCordZTree(0);
            }
        }
    }
}

// Função para iniciar todas as filas;
void Field::initQueues()
{
    for (float i = 0; i <= 180; i++)
    {
        cordY.push_back(i*200);
        cordZRight.push_back(randMountain());
        cordZLeft.push_back(randMountain());   
    }

    treesRight.push_back(Tree(colorBG, vec3(rand()%100+100, 2000 + (rand() % 1000 - 500),-6.7f)));
    treesLeft.push_back(Tree(colorBG, vec3((rand()%100+100)*-1, 2000 +(rand() % 1000 - 500),-6.7f)));

    for (int i = 0; treesRight.back().getCordTree().y < 36000; i++)
    {
        treesRight.push_back(Tree(colorBG, vec3(rand()%100+200, 
                                                    treesRight[i].getCordTree().y + 2000 + (rand() % 1000 - 500),
                                                    0)));
        if(treesRight.back().getCordTree().y > 14000)
        {
            treesRight.back().setCordZTree(-(treesRight.back().getCordTree().y-14000)/100);
        }
    }
    
    for (int i = 0; treesLeft.back().getCordTree().y < 36000; i++)
    {   
        treesLeft.push_back(Tree(colorBG, vec3((rand() % 100 + 200) * -1,
                                                   treesLeft[i].getCordTree().y + 2000 + (rand() % 1000 - 500),
                                                   0)));
        if(treesLeft.back().getCordTree().y > 14000)
        {
            treesLeft.back().setCordZTree(-(treesLeft.back().getCordTree().y-14000)/100);
        }
    }
}

// Função para gerar deformidade das montanhas
vector<int> Field::randMountain()
{
    vector<int> aux;
    for (int j = 0; j < 30; j++)
    {
        if (j <= 13) aux.push_back(0);
        if (j == 14) aux.push_back(rand() % 10);
        if (j == 15) aux.push_back(rand() % 30 + 10);
        if (j == 16) aux.push_back(rand() % 60 + 30);
        if (j == 17) aux.push_back(rand() % 80 + 60);
        if (j == 18) aux.push_back(rand() % 100 + 80);
        if (j == 19) aux.push_back(rand() % 120 + 100);
        if (j == 20) aux.push_back(rand() % 130 + 120);
        if (j == 21) aux.push_back(rand() % 140 + 130);
        if (j == 22) aux.push_back(rand() % 150 + 140);
        if (j >= 23) aux.push_back(rand() % 155 + 150);
    }
    return aux;
}