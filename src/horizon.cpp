#include "../header/horizon.h"

#include <GL/gl.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Horizon::Horizon(GLubyte colorSun[3], GLubyte colorLight[3], GLubyte colorStars[3], GLubyte colorBG[3], glm::vec3 sunPos, float scale, bool lines, bool city)
{
    for (int i = 0; i < 3; i++)
    {
        this->colorSun[i] = colorSun[i];
        this->colorLight[i] = colorLight[i];
        this->colorStars[i] = colorStars[i];
        this->colorBG[i] = colorBG[i];
    }

    this->scale = scale;
    this->sunPos = sunPos;
    this->lines = lines;
    this->city = city;
    
    for (float i = -1; i < 1.1; i += 0.1)
    {
        for (float j = -4; j <= 4; j += 0.1)
        {
            if (rand() % 10 == 1)
            {
                starCord.push_back(glm::vec3(j + ((rand() % 2 - 1) * 0.05), i, 0));
            }
        }
    }
}

void Horizon::draw(glm::vec3 camPos)
{
    // Gambiara com canculo de tangente inversa pra fazer o Sol alinhar com a câmera
    rotCam = 90 + (90 - (atan(sunPos.y + camPos.y / sunPos.z + camPos.z) * (180 / M_PI)));
    this->sunPos.x = camPos.x;
    drawStars();
    drawSun();
    drawSunGlow();
    if (lines)
    {
        drawSunLines();
    }
    if (city)
    {
        drawSunFrontGlow();
        drawCity();
        drawGlowCity();
    }
}

void Horizon::drawStars()
{
    glPushMatrix();
        glTranslatef(sunPos.x, sunPos.y + 100, sunPos.z);
        glRotatef(rotCam, 1, 0, 0); // Rotaciona para ficar alinhado com a câmera
        glColor3ubv(colorStars);
        
        for (int i = 0; i < starCord.size(); i++)
        {
            glPushMatrix();
                glTranslatef(starCord[i].x * scale, starCord[i].y * scale, starCord[i].z * scale);
                glScalef(scale / 100, scale / 100, 1);
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0, 0, 0);
                    for (float angulo = 0; angulo <= 360; angulo += 30)
                    {
                        float x = cos(angulo * M_PI / 180.0);
                        float y = sin(angulo * M_PI / 180.0);
                        glVertex3f(x, y, 0);
                    }
                glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void Horizon::drawSun()
{
    glPushMatrix();
        glTranslatef(sunPos.x, sunPos.y, sunPos.z);
        glRotatef(rotCam, 1, 0, 0); // Rotaciona para ficar alinhado com a câmera
        glColor3ubv(colorSun);
        glScalef(scale, scale, 1);
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, 0, 0);
            for (float angulo = 0; angulo <= 360; angulo += 1)
            {
                float x = cos(angulo * M_PI / 180.0);
                float y = sin(angulo * M_PI / 180.0);
                glVertex3f(x, y, 0);
            }
        glEnd();
    glPopMatrix();
}

void Horizon::drawSunLines()
{
    glPushMatrix();
        glTranslatef(sunPos.x, sunPos.y - 20, sunPos.z);
        glRotatef(rotCam, 1, 0, 0); // Rotaciona para ficar alinhado com a câmera
        glScalef(scale, scale, 1);
        glColor3ubv(colorLight);

        // Coloquei os valor tudo na mão mesmo porque tava com dificuldade de pensar em como fazer isso usando
        // as função de circulo...

        glBegin(GL_QUADS);
            glVertex3f(1, -0.05, 0); // 1
            glVertex3f(1, 0, 0);
            glVertex3f(-1, 0, 0);
            glVertex3f(-1, -0.05, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.99, -0.15, 0); // 2
            glVertex3f(1, -0.10, 0);
            glVertex3f(-1, -0.10, 0);
            glVertex3f(-0.99, -0.15, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.97, -0.25, 0); // 3
            glVertex3f(0.98, -0.20, 0);
            glVertex3f(-0.98, -0.20, 0);
            glVertex3f(-0.97, -0.25, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.94, -0.35, 0); // 4
            glVertex3f(0.96, -0.30, 0);
            glVertex3f(-0.96, -0.30, 0);
            glVertex3f(-0.94, -0.35, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.90, -0.45, 0); // 5
            glVertex3f(0.92, -0.40, 0);
            glVertex3f(-0.92, -0.40, 0);
            glVertex3f(-0.90, -0.45, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.84, -0.55, 0); // 6
            glVertex3f(0.87, -0.50, 0);
            glVertex3f(-0.87, -0.50, 0);
            glVertex3f(-0.84, -0.55, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.76, -0.65, 0); // 7
            glVertex3f(0.81, -0.60, 0);
            glVertex3f(-0.81, -0.60, 0);
            glVertex3f(-0.76, -0.65, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.67, -0.75, 0); // 8
            glVertex3f(0.72, -0.70, 0);
            glVertex3f(-0.72, -0.70, 0);
            glVertex3f(-0.67, -0.75, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.53, -0.85, 0); // 9
            glVertex3f(0.61, -0.80, 0);
            glVertex3f(-0.61, -0.80, 0);
            glVertex3f(-0.53, -0.85, 0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0.33, -0.95, 0); // 10
            glVertex3f(0.45, -0.90, 0);
            glVertex3f(-0.45, -0.90, 0);
            glVertex3f(-0.33, -0.95, 0);
        glEnd();
    glPopMatrix();
}

void Horizon::drawSunGlow()
{
    // Brilho de fundo atrás do Sol
    glPushMatrix();
        glTranslatef(sunPos.x, sunPos.y + 10, sunPos.z);
        glRotatef(rotCam, 1, 0, 0); // Rotaciona para ficar alinhado com a câmera
        glScalef(scale, scale, 1);
        glBegin(GL_QUAD_STRIP);
            for (float angulo = 0; angulo <= 360; angulo += 1)
            {
                float x = cos(angulo * M_PI / 180.0);
                float y = sin(angulo * M_PI / 180.0);
                glColor3ubv(colorLight);
                glVertex3f(x, y, 1);
                glColor4f(0, 0, 0, 0);
                glVertex3f(x * 1.6, y * 1.6, 1);
            }
        glEnd();
    glPopMatrix();
}

void Horizon::drawSunFrontGlow()
{
    // Brilho de fundo na frente do Sol
    glPushMatrix();
    glTranslatef(0, sunPos.y - 100, 0);
    glRotatef(rotCam, 1, 0, 0); // Rotaciona para ficar alinhado com a câmera
    glScalef(scale, scale, 0);
    glBegin(GL_QUADS);
    glColor3ubv(colorLight);
    glVertex3f(-4, -0.1, 0);
    glVertex3f(4, -0.1, 0);
    glColor4f(0, 0, 0, 0);
    glVertex3f(4, 2, 0);
    glVertex3f(-4, 2, 0);
    glEnd();
    glPopMatrix();
}

void Horizon::drawCity()
{
    glPushMatrix();
    glTranslatef(sunPos.x, sunPos.y - 200, -0.02 * scale);
    glRotatef(rotCam, 1, 0, 0);
    glScalef(scale, scale, 1);
    glColor3ubv(colorBG);

    glPushMatrix();
    glTranslatef(-0.65, -0.01, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0, 0);
    glVertex3f(0.10, 0, 0);
    glVertex3f(0.10, 0.20, 0);
    glVertex3f(0.08, 0.20, 0);
    glVertex3f(0.08, 0.30, 0);
    glVertex3f(0.02, 0.30, 0);
    glVertex3f(0.02, 0.15, 0);
    glVertex3f(0, 0.15, 0);
    glVertex3f(0, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.06, 0.30, 0);
    glVertex3f(0.06, 0.35, 0);
    glVertex3f(0.04, 0.30, 0);
    glVertex3f(0.04, 0.35, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, -0.01, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0.10, 0, 0);
    glVertex3f(0.10, 0.15, 0);
    glVertex3f(0.04, 0.20, 0);
    glVertex3f(0, 0.20, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.02, 0.2, 0);
    glVertex3f(0.02, 0.23, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, -0.01, 0);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.10, 0);
    glVertex3f(0.30, 0.10, 0);
    glVertex3f(0.30, 0, 0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.20, 0.10, 0);
    glVertex3f(0.20, 0.20, 0);
    glVertex3f(0.25, 0.20, 0);
    glVertex3f(0.25, 0.10, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0.10, 0);
    glVertex3f(0.10, 0.10, 0);
    glVertex3f(0.10, 0.15, 0);
    glVertex3f(0.08, 0.15, 0);
    glVertex3f(0.08, 0.30, 0);
    glVertex3f(0.02, 0.30, 0);
    glVertex3f(0.02, 0.25, 0);
    glVertex3f(0, 0.25, 0);
    glVertex3f(0, 0.10, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.06, 0.30, 0);
    glVertex3f(0.06, 0.35, 0);
    glVertex3f(0.22, 0.20, 0);
    glVertex3f(0.22, 0.25, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.35, -0.01, 0);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.10, 0);
    glVertex3f(0.20, 0.10, 0);
    glVertex3f(0.20, 0, 0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.1, 0.10, 0);
    glVertex3f(0.1, 0.20, 0);
    glVertex3f(0.15, 0.15, 0);
    glVertex3f(0.15, 0.10, 0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.18, 0.10, 0);
    glVertex3f(0.18, 0.15, 0);
    glVertex3f(0.20, 0.15, 0);
    glVertex3f(0.20, 0.10, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, -0.01, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0, 0);
    glVertex3f(0.10, 0, 0);
    glVertex3f(0.10, 0.20, 0);
    glVertex3f(0.08, 0.20, 0);
    glVertex3f(0.08, 0.30, 0);
    glVertex3f(0.02, 0.30, 0);
    glVertex3f(0.02, 0.15, 0);
    glVertex3f(0, 0.15, 0);
    glVertex3f(0, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.06, 0.30, 0);
    glVertex3f(0.06, 0.35, 0);
    glVertex3f(0.04, 0.30, 0);
    glVertex3f(0.04, 0.35, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.04, -0.01, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0.10, 0, 0);
    glVertex3f(0.10, 0.15, 0);
    glVertex3f(0.04, 0.20, 0);
    glVertex3f(0, 0.20, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.02, 0.2, 0);
    glVertex3f(0.02, 0.23, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.16, -0.01, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.10, 0);
    glVertex3f(0.04, 0.15, 0);
    glVertex3f(0.10, 0.15, 0);
    glVertex3f(0.10, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.65, -0.01, 0);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.20, 0);
    glVertex3f(0.10, 0.20, 0);
    glVertex3f(0.10, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

void Horizon::drawGlowCity()
{
    glPushMatrix();
    glTranslatef(0, sunPos.y - 300, 0);
    glRotatef(rotCam, 1, 0, 0); // Rotaciona para ficar alinhado com a câmera
    glScalef(scale, scale, 0);
    glBegin(GL_QUADS);
    glColor3ubv(colorLight);
    glVertex3f(-2, -0.1, 0);
    glVertex3f(2, -0.1, 0);
    glColor4f(0, 0, 0, 0);
    glVertex3f(2, 0.4, 0);
    glVertex3f(-2, 0.4, 0);
    glEnd();
    glPopMatrix();
}