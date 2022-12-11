#include "../header/funnyTunnel.h"

FunnyTunnel::FunnyTunnel(GLubyte colorTunnel1[3], GLubyte colorTunnel2[3],
                         GLubyte colorTunnel3[3], GLubyte colorBG[3], Textures *textures)
{
    for (int i = 0; i < 3; i++)
    {
        this->colorTunnel1[i] = colorTunnel1[i];
        this->colorTunnel2[i] = colorTunnel2[i];
        this->colorTunnel3[i] = colorTunnel3[i];
        this->colorBG[i] = colorBG[i];
    }

    for (int i = -3; i < 80; i++)
    {
        cordY.push_back(i * 1000);
    }

    this->textures = textures;
}

void FunnyTunnel::draw(float speed, int direction)
{
    auxRot += (speed / 90) / 2 * direction;

    if (auxRot < 0)
        auxRot = 360 + auxRot;
    if (auxRot > 360)
        auxRot = auxRot - 360;

    updTunnel(speed);

    glLineWidth(1.0f);
    drawMode(GL_FILL, colorBG, 100.f);

    glLineWidth(2.0f);
    if (starCount == 0)
        drawMode(GL_LINE, colorTunnel1, 99.8f);
    if (starCount == 1)
        drawMode(GL_LINE, colorTunnel2, 99.8f);
    if (starCount == 2)
        drawMode(GL_LINE, colorTunnel3, 99.8f);
}

void FunnyTunnel::drawMode(int mode, GLubyte color[3], float scale)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    drawStar();
    glColor3ubv(color);
    drawObstacle();
    drawTunnel(scale);
}

void FunnyTunnel::drawObstacle()
{
    for (int i = 0; i < obstacle[0].size(); i++)
    {
        glPushMatrix();
        glTranslatef(0, 0, 90);
        glRotatef(obstacle[1][i] + auxRot, 0, 1, 0);
        glTranslatef(0, 0, -90);
        float size = starCount * 40 + 40;

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, obstacle[0][i], size);
        glVertex3f(-25.8, obstacle[0][i] - 500, -6.5);
        glVertex3f(25.8, obstacle[0][i] - 500, -6.5);
        glVertex3f(25.8, obstacle[0][i] + 500, -6.5);
        glVertex3f(-25.8, obstacle[0][i] + 500, -6.5);
        glVertex3f(-25.8, obstacle[0][i] - 500, -6.5);
        glEnd();

        glPopMatrix();
    }
}

void FunnyTunnel::drawStar()
{
    if (!star.empty())
    {
        glPushMatrix();
        glTranslatef(0, 0, 90);
        glRotatef(star[1] + auxRot, 0, 1, 0);
        glTranslatef(0, 0, -90);
        glColor3f(1, 1, 1);

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, star[0], 0);
        glVertex3f(-10, star[0] - 100, 15);
        glVertex3f(10, star[0] - 100, 15);
        glVertex3f(10, star[0] + 100, 15);
        glVertex3f(-10, star[0] + 100, 15);
        glVertex3f(-10, star[0] - 100, 15);
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, star[0], 30);
        glVertex3f(-10, star[0] - 100, 15);
        glVertex3f(10, star[0] - 100, 15);
        glVertex3f(10, star[0] + 100, 15);
        glVertex3f(-10, star[0] + 100, 15);
        glVertex3f(-10, star[0] - 100, 15);
        glEnd();

        glPopMatrix();
    }
}

void FunnyTunnel::drawTunnel(float scale)
{
    glPushMatrix();
    glTranslatef(0, 0, 90);
    glRotatef(auxRot, 0, 1, 0);
    textures->bind(TEX_WALL2);
    for (int i = 0; i < cordY.size() - 1; i++)
    {
        glPushMatrix();
        glScalef(scale, 1, scale);
        glColor3f(1, 1, 1);

        glBegin(GL_QUAD_STRIP);
        for (float angulo = 0; angulo <= 360; angulo += 30)
        {
            float x = cos(angulo * M_PI / 180.0);
            float z = sin(angulo * M_PI / 180.0);
            glTexCoord2f(angulo / 360, 0);
            glVertex3f(x, cordY[i], z);
            glTexCoord2f(angulo / 360, 1);
            glVertex3f(x, cordY[i + 1], z);
        }
        glEnd();

        glPopMatrix();
    }
    textures->unbind();
    glPopMatrix();
}

void FunnyTunnel::updTunnel(float speed)
{
    if (!star.empty())
    {
        star[0] = star[0] - speed;
        if (star[0] < -200)
        {
            star.clear();
        }
    }

    if (!obstacle[0].empty())
    {
        if (obstacle[0].back() < 77000 + starCount * 1000)
        {
            newObstacle();
        }
    }
    else
    {
        newObstacle();
    }

    for (int i = 0; i < obstacle[0].size(); i++)
    {
        obstacle[0][i] = obstacle[0][i] - speed;
        if (obstacle[0][i] <= -2000)
        {
            obstacle[0].pop_front();
            obstacle[1].pop_front();
            newObstacle();
            i--;
        }
    }

    for (int i = 0; i < cordY.size(); i++)
    {
        cordY[i] -= speed;
        if (cordY[i] <= -2000)
        {
            cordY.pop_front();
            cordY.push_back(cordY.back() + 1000);
            i--;
        }
    }
}

void FunnyTunnel::newObstacle()
{
    if (star.empty() && rand() % 20 == 1)
    {
        star.push_back(cordY.back() - 500);
        if (obstacle[1].empty())
        {
            star.push_back((360 / 12) * (rand() % 12) + 15);
        }
        else
        {
            float aux;
            do
            {
                aux = (360 / 12) * (rand() % 12) + 15;
            } while (aux == obstacle[1].back());

            star.push_back(aux);
        }
    }
    else
    {
        obstacle[0].push_back(cordY.back() - 500);
        if (obstacle[1].empty())
        {
            obstacle[1].push_back((360 / 12) * (rand() % 12) + 15);
        }
        else
        {
            float aux;
            do
            {
                aux = (360 / 12) * (rand() % 12) + 15;
            } while (aux == obstacle[1].back());

            obstacle[1].push_back(aux);
        }
    }
}

int FunnyTunnel::checkColision(float speed)
{
    if (!obstacle[0].empty() && speed > 0)
    {
        int i = 0;
        while (i < obstacle[0].size())
        {
            if (obstacle[0][i] - 500 < 30 + speed && obstacle[0][i] + 500 > -30 + speed)
            {
                float aux = obstacle[1][i] + auxRot;

                if (aux < 0)
                    aux = 360 + aux;
                if (aux > 360)
                    aux = aux - 360;

                if (aux < 20 || aux > 340)
                {
                    int i = 0;
                    while (i < 10)
                    {
                        obstacle[0].pop_front();
                        obstacle[1].pop_front();
                        i++;
                    }
                    star.clear();
                    return 2;
                }
                break;
            }
            i++;
        }
    }

    if (!star.empty())
    {
        if (star[0] + 500 > 30 + speed && star[0] - 500 < 30 + speed)
        {
            float aux = star[1] + auxRot;

            if (aux < 0)
                aux = 360 + aux;
            if (aux > 360)
                aux = aux - 360;

            if (aux < 20 || aux > 340)
            {
                star.clear();
                starCount++;
                if (starCount == 3)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}