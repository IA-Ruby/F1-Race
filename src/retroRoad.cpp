#include "../header/retroRoad.h"

RetroRoad::RetroRoad(GLubyte colorRoad[3], GLubyte colorField[3], GLubyte colorBG[3], Textures* textures)
:
    enemy( colorBG, colorRoad, vec3(0,600,0), 150, textures)
{
    for (int i = 0; i < 3; i++)
    {
        this->colorRoad[i] = colorRoad[i];
        this->colorField[i] = colorField[i];
        this->colorBG[i] = colorBG[i];
    }
    
    initQueues();
}

void RetroRoad::draw(float speed)
{
    updRoad(speed);
    drawMountains(GL_LINE, colorField);
    drawMountains(GL_FILL, colorBG);
    drawTrees();
    drawRoad();
    enemy.draw();

    // if(finish)
    // {
    //     drawTunnel(GL_LINE, colorRetroRoad);
    //     drawTunnel(GL_FILL, colorBG);
    // }
}

// Desenha a pista
void RetroRoad::drawRoad()
{
    glPushMatrix();
        glTranslatef(0, 6400, -5.1);
        glColor3ubv(colorBG);
        drawQuad(80.f, 8000.f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-80, 6400, -5);
        glColor3ubv(colorRoad);
        drawQuad(3.f, 8000.f);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(80, 6400, -5);
        glColor3ubv(colorRoad);
        drawQuad(3.f, 8000.f);
    glPopMatrix();

    // Desenha as faixas
    for (int i = 0; i < cordYRoad.size(); i++)
    {
        glPushMatrix();
            glTranslatef(0, cordYRoad[i], -5);
            glColor3ubv(colorRoad);
            drawQuad(3.f, 100.f);
        glPopMatrix();
    }
}

// Desenha quadrados
void RetroRoad::drawQuad(float x, float y)
{
    glBegin(GL_QUADS);
        glVertex3f( x, -y, 0);
        glVertex3f( x,  y, 0);
        glVertex3f(-x,  y, 0);
        glVertex3f(-x, -y, 0);
    glEnd();
}

// Desenha o campo e as montanhas
void RetroRoad::drawMountains(int mode, GLubyte color[3])
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    for (int i = -1; i <= 1; i += 2)
    {
        glPushMatrix();
            glTranslatef(83 * i, 0, -6.7);
            glColor3ubv(color);
            for (int j = 0; j < (cordYField.size() - 1); j++)
            {
                glBegin(GL_QUAD_STRIP);
                for (int k = 0; k < 30; k++)
                {
                    if(cordYField[j] <= 14000)
                    {
                        glVertex3f(k * 20 * i,     cordYField[j],     cordZRight[j][k]);
                        glVertex3f(k * 20 * i, cordYField[j + 1], cordZRight[j + 1][k]);   
                    }    
                    else
                    {
                        glVertex3f(k * 20 * i,     cordYField[j],     cordZRight[j][k] - (cordYField[j]-14000)/100);
                        glVertex3f(k * 20 * i, cordYField[j + 1], cordZRight[j + 1][k] - (cordYField[j]-14000)/100);
                    }
                }
                glEnd();
            }
        glPopMatrix();
    }
}

// Desenha as arvores
void RetroRoad::drawTrees()
{
    for (int i = 0; i < treesLeft.size(); i++)
    {
        glPushMatrix();
            glTranslatef(   treesLeft[i].getCordTree().x, 
                            treesLeft[i].getCordTree().y, 
                            treesLeft[i].getCordTree().z-6.7);
            treesLeft[i].draw();
        glPopMatrix();
    }
    
    for (int i = 0; i < treesRight.size(); i++)
    {    
        glPushMatrix();
            glTranslatef(   treesRight[i].getCordTree().x, 
                            treesRight[i].getCordTree().y, 
                            treesRight[i].getCordTree().z-6.7);
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
void RetroRoad::updRoad(float speed)
{  
    // Atualiza as linhas
    for (int i = 0; i < cordYRoad.size(); i++)
    {
        cordYRoad[i] -= speed;
        if (cordYRoad[i] < -200.f)
        {
            cordYRoad.push_back(cordYRoad[i] + (cordYRoad.size() * 500.f));
            cordYRoad.pop_front();
            i--;
        }
    } 

    // Atualiza as coordenadas das linhas e montanhas
    for (int i = 0; i < cordYField.size(); i++)
    {
        cordYField[i] -= speed;
 
        if (cordYField[i] < -400.f)
        {
            cordYField.push_back(cordYField[i] + (cordYField.size() * 200));
            cordYField.pop_front();
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

int RetroRoad::updEnemy(float time, Driver &player)
{
    if(enemy.getCarPos().y < -10000)
    {
        enemy.setCarPosY(enemy.getCarPos().y + enemy.getSpeed() - player.getSpeed());
        player.setCarPosY(player.getCarPos().y + player.getSpeed());
        
        if(player.getCarPos().y > 20000)
        {
            player.setCarPos(vec3(player.getCarPos().x,0,0));
            enemy.setCarPos(vec3(300,0,0));
            return 2;
        }
        else if(player.getCarPos().y > 14000)
        {
            player.setCarPosZ(-(player.getCarPos().y - 14000) /100);
        }
    }
    else if(enemy.getCarPos().y+30 < player.getCarPos().x-30)
    {
        enemy.slowDown(time);
        enemy.setCarPosY(enemy.getCarPos().y + enemy.getSpeed() - player.getSpeed());
    }
    else if(enemy.getCarPos().y < 14000)
    {
        enemy.speedUp(time);
        enemy.setCarPosY(enemy.getCarPos().y + enemy.getSpeed() - player.getSpeed());
        if( player.getCarPos().y+30 < enemy.getCarPos().y-30 
            && player.getCarPos().y+30 < enemy.getCarPos().y-30-player.getSpeed())
        {
            enemy.turn(0);
            if(player.getCarPos().x+15 < enemy.getCarPos().x+10) enemy.turn(-1);
            if(player.getCarPos().x-15 > enemy.getCarPos().x-10) enemy.turn( 1);   

            enemy.setCarPosX(enemy.getCarPos().x + (enemy.getSpeed() * enemy.getDirection())/100); 
            if(enemy.getCarPos().x >  60.f) enemy.setCarPosX( 60.f);
            if(enemy.getCarPos().x < -60.f) enemy.setCarPosX(-60.f);
        }
        else 
        {
            if( player.getCarPos().x+15 > enemy.getCarPos().x 
                && player.getCarPos().x-15 < enemy.getCarPos().x)
            { 
                return 1;
            }
        }   
    }
    else 
    {
        enemy.setCarPosZ(-(enemy.getCarPos().y-14000)/100);
        enemy.brake(time);   
        enemy.setCarPosY(enemy.getCarPos().y + enemy.getSpeed() - player.getSpeed());
    }
    return 0;
}

// Função para iniciar todas as filas;
void RetroRoad::initQueues()
{
    for (int i = 0; i < 30; i++)
    {
        cordYRoad.push_back(i * 500.f);
    }

    for (int i = 0; i <= 180; i++)
    {
        cordYField.push_back(i*200);
        cordZRight.push_back(randMountain());
        cordZLeft.push_back(randMountain());   
    }

    treesRight.push_back(Tree(colorBG, vec3(rand()%100+100, 2000 + (rand() % 1000 - 500),-6.7f)));

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
    
    treesLeft.push_back(Tree(colorBG, vec3((rand()%100+100)*-1, 2000 +(rand() % 1000 - 500),-6.7f)));
    
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
vector<int> RetroRoad::randMountain()
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