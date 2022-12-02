#include "../header/trainTunnel.h"

TrainTunnel::TrainTunnel(GLubyte colorRoad[3], GLubyte colorWall[3], GLubyte colorBG[3], Textures* textures)
{
    for (int i = 0; i < 3; i++)
    {
        this->colorRoad[i] = colorRoad[i];
        this->colorWall[i] = colorWall[i];
        this->colorBG[i] = colorBG[i];
    }
    
    for (int i = -2; i < 300; i++)
    {
        cordY.push_back(i * 400);
    }

    this->textures = textures;

    trainPos = cordY.back();
}

void TrainTunnel::draw(float speed)
{
    drawTrain(speed);
    updTunnel(speed);
    drawMode(GL_LINE, colorRoad, colorWall);
    drawMode(GL_FILL, colorBG, colorBG);
}

void TrainTunnel::drawMode(int mode, GLubyte color1[3], GLubyte color2[3])
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
        glTranslatef(0, 0, -5.1);
        for (int i = 0; i < cordY.size() - 1; i++)
        {
            glColor3f(1,1,1);
            textures->bind(TEX_RAILWAY);
            glBegin(GL_QUADS);
                glTexCoord2f(0,0); glVertex3f(-80,     cordY[i], 0);
                glTexCoord2f(0.95,0); glVertex3f( 80,     cordY[i], 0);
                glTexCoord2f(0.95,1); glVertex3f( 80, cordY[i + 1], 0);
                glTexCoord2f(0,1); glVertex3f(-80, cordY[i + 1], 0);
            glEnd();
            textures->unbind();
            
            glPushMatrix();
                glScalef(80, 1, 80);
                glColor3ubv(color2);
                glBegin(GL_QUAD_STRIP);
                    for (float angulo = 0; angulo <= 180; angulo += 20)
                    {
                        float x = cos(angulo * M_PI / 180.0);
                        float z = sin(angulo * M_PI / 180.0);
                        glVertex3f(x,     cordY[i], z);
                        glVertex3f(x, cordY[i + 1], z);
                    }
                glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void TrainTunnel::drawTrain(float speed)
{
    glColor3f(0.7,0.7,0.7);
    textures->bind(TEX_TRAIN);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1); glVertex3f( -35, trainPos, 0);
        glTexCoord2f(0,1); glVertex3f(  35, trainPos, 0);
        glTexCoord2f(0,0); glVertex3f(  35, trainPos, 50);
        glTexCoord2f(1,0); glVertex3f( -35, trainPos, 50);
    glEnd();
    textures->unbind();
}

void TrainTunnel::updTunnel(float speed)
{
    if(distance > 4000) trainPos -= 130 + speed;
    else distance += speed;

    for (int i = 0; i < cordY.size(); i++)
    {
        cordY[i] -= speed;
        if (cordY[i] <= -800)
        {
            cordY.pop_front();
            cordY.push_back(cordY.back() + 400);
            i--;
        }
    }
}

float TrainTunnel::getTrainPos()
{
    return trainPos;
}