#include "../header/spiral.h"

Spiral::Spiral(GLubyte colorRoad[3], GLubyte colorBG[3], Textures *textures)
{
    for (int i = 0; i < 3; i++)
    {
        this->colorRoad[i] = colorRoad[i];
        this->colorBG[i] = colorBG[i];
    }

    for (int i = 0; i < 30; i++)
    {
        cordY.push_back(i * 7200);
    }
    this->textures = textures;
}

void Spiral::draw(float speed)
{
    glPushMatrix();
    updSpiral(speed);
    drawMode(GL_FILL, colorBG);
    drawMode(GL_LINE, colorRoad);
    glPopMatrix();
}

void Spiral::drawMode(int mode, GLubyte color[3])
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
    glTranslatef(0, 0, 290);
    textures->bind(TEX_FLOOR);
    glRotatef(-auxRot, 1, 0, 0);
    for (int i = 0; i < cordY.size(); i++)
    {
        glPushMatrix();
        glRotatef(90, 0, 0, 1);
        glTranslatef(0, cordY[i] - 5600, 0);
        glScalef(300, 1, 300);
        glColor3f(1, 1, 1);

        glBegin(GL_QUAD_STRIP);
        for (float angulo = 0; angulo <= 360; angulo += 10)
        {
            float x = cos(angulo * M_PI / 180.0);
            float z = sin(angulo * M_PI / 180.0);
            glTexCoord2f(angulo / 360, 0);
            glVertex3f(x, angulo * 20, z);
            glTexCoord2f(angulo / 360, 1);
            glVertex3f(x, angulo * 20 + 400, z);
        }
        glEnd();

        glPopMatrix();
    }
    textures->unbind();

    glPopMatrix();
}

void Spiral::updSpiral(float speed)
{
    for (int i = 0; i < cordY.size(); i++)
    {
        cordY[i] -= speed;
        if (cordY[i] < -20000)
        {
            cordY.pop_front();
            cordY.push_back(cordY.back() + 7200);
            i--;
        }
    }

    auxRot += speed / 20;

    if (auxRot > 360)
        auxRot -= 360;
    if (auxRot < 0)
        auxRot += 360;
}