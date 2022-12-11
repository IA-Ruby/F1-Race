#include "../header/car.h"

Car::Car(GLubyte colorCar[3], GLubyte colorOutline[3], vec3 pos, float maxSpeed, Textures *textures)
{
    for (int i = 0; i < 3; i++)
    {
        this->colorCar[i] = colorCar[i];
        this->colorOutline[i] = colorOutline[i];
    }
    this->carPos = pos;
    this->textures = textures;
    this->maxSpeed = maxSpeed;
}

void Car::draw()
{
    glLineWidth(4.0f);
    drawMode(GL_LINE, colorOutline);
    glLineWidth(1.0f);
    drawMode(GL_FILL, colorCar);
}

void Car::drawMode(int mode, GLubyte color[3])
{
    float
        // Eixo X
        outX = 14.6,
        maxX = 13.25, midX = 5, medX = 10,
        tMaxX = 10, tMinX = 9.5,

        // Eixo Y
        maxY = 35, lowY = -30, medY = 21, midY = 9, mid2Y = 8, med2Y = 20,
        tMaxY = -28, tMedY = -29, tMidY = -30, tLowY = -31, tMinY = -32,

        // Eixo Z
        maxZ = 15, lowZ = -1.5, dwnZ = 0, midZ = 7, medZ = 9,
        tMaxZ = 14, tMinZ = 13;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
    glTranslatef(carPos.x, carPos.y, carPos.z);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotZ, 0, 0, 1);
    glColor3ubv(color);

    // Atualização da variavel de rotação
    wheelRot = wheelRot + (0.25 * speed);
    if (wheelRot >= 360)
        wheelRot = (0.25 * speed);

    //  Rodas
    for (int i = -1; i <= 1; i += 2)
    {
        for (int j = -1; j <= 1; j += 2)
        {
            glPushMatrix();
            glTranslatef((i * 10), (j * 15), 0);
            if (i < 0)
            {
                glRotatef(-90.f, 0, 1, 0);
                glRotatef(wheelRot, 0, 0, 1);
            }
            else
            {
                glRotatef(90.f, 0, 1, 0);
                glRotatef(-wheelRot, 0, 0, 1);
            }
            drawWheel(5.f, 2.5f);
            glPopMatrix();
        }
    }

    // Buracos das Rodas
    textures->bind(TEX_CARTAIL);
    if (mode == GL_FILL)
    {

        for (int i = -1; i <= 1; i += 2)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                glPushMatrix();
                glTranslatef((i * 5), (j * 15), 0);
                glScalef(6, 6, 6);

                if (i < 0)
                    glRotatef(180.f, 0, 0, 1);

                glBegin(GL_QUAD_STRIP);
                for (float angulo = 0; angulo <= 180; angulo += 20)
                {
                    float y = cos(angulo * M_PI / 180.0);
                    float z = sin(angulo * M_PI / 180.0);
                    glTexCoord2f(angulo, 0);
                    glVertex3f(0, y, z);
                    glTexCoord2f(angulo, 1);
                    glVertex3f(1.6, y, z);
                }
                glEnd();
                glPopMatrix();
            }
        }
    }

    for (int i = -1; i <= 1; i += 2)
    {
        for (int j = -1; j <= 1; j += 2)
        {
            glPushMatrix();
            glTranslatef((i * 5), (j * 15), 0);
            glScalef(6, 6, 6);

            if (i < 0)
                glRotatef(180.f, 0, 0, 1);

            glBegin(GL_QUAD_STRIP);
            for (float angulo = 0; angulo <= 180; angulo += 20)
            {
                float y = cos(angulo * M_PI / 180.0);
                float z = sin(angulo * M_PI / 180.0);
                glTexCoord2f(angulo, 0);
                glVertex3f(1.6, y, z);
                glTexCoord2f(angulo, 1);
                glVertex3f(1.4, y * 1.2, z * 1.2);
            }
            glEnd();
            glPopMatrix();
        }
    }

    glPushMatrix();
    // Parte de baixo do carro
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(midX, -medY, lowZ);
    glTexCoord2f(1, 0);
    glVertex3f(midX, medY, lowZ);
    glTexCoord2f(1, 1);
    glVertex3f(-midX, medY, lowZ);
    glTexCoord2f(0, 1);
    glVertex3f(-midX, -medY, lowZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, -midY, lowZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, midY, lowZ);
    glTexCoord2f(1, 1);
    glVertex3f(midX, midY, lowZ);
    glTexCoord2f(0, 1);
    glVertex3f(midX, -midY, lowZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-midX, -midY, lowZ);
    glTexCoord2f(1, 0);
    glVertex3f(-midX, midY, lowZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, midY, lowZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, -midY, lowZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, lowY, lowZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, -medY, lowZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, -medY, lowZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, lowY, lowZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, maxY, lowZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, medY, lowZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, medY, lowZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, maxY, lowZ);
    glEnd();

    for (int i = -1; i <= 1; i += 2)
    {
        for (int j = -1; j <= 1; j += 2)
        {
            // Preencher os buracos
            if (mode == GL_FILL)
            {
                glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(midX * i, midY * j, dwnZ);
                glTexCoord2f(1, 0);
                glVertex3f(midX * i, midY * j, lowZ);
                glTexCoord2f(1, 1);
                glVertex3f(outX * i, midY * j, lowZ);
                glTexCoord2f(0, 1);
                glVertex3f(outX * i, midY * j, dwnZ);
                glEnd();

                glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(midX * i, medY * j, dwnZ);
                glTexCoord2f(1, 0);
                glVertex3f(midX * i, medY * j, lowZ);
                glTexCoord2f(1, 1);
                glVertex3f(outX * i, medY * j, lowZ);
                glTexCoord2f(0, 1);
                glVertex3f(outX * i, medY * j, dwnZ);
                glEnd();
            }
            // Complemento do relevo
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f((maxX + 0.1) * i, (medY + 1.2) * j, dwnZ);
            glTexCoord2f(1, 0);
            glVertex3f((maxX + 0.1) * i, (medY + 1.2) * j, lowZ);
            glTexCoord2f(1, 1);
            glVertex3f(outX * i, medY * j, lowZ);
            glTexCoord2f(0, 1);
            glVertex3f(outX * i, medY * j, dwnZ);
            glEnd();

            glBegin(GL_TRIANGLES);
            glTexCoord2f(0, 1);
            glVertex3f((maxX + 0.1) * i, (medY + 1.2) * j, lowZ);
            glTexCoord2f(1, 1);
            glVertex3f((maxX + 0.1) * i, medY * j, lowZ);
            glTexCoord2f(1, 0);
            glVertex3f(outX * i, medY * j, lowZ);
            glEnd();

            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f((maxX + 0.1) * i, (midY - 1.2) * j, dwnZ);
            glTexCoord2f(1, 0);
            glVertex3f((maxX + 0.1) * i, (midY - 1.2) * j, lowZ);
            glTexCoord2f(1, 1);
            glVertex3f(outX * i, midY * j, lowZ);
            glTexCoord2f(0, 1);
            glVertex3f(outX * i, midY * j, dwnZ);
            glEnd();

            glBegin(GL_TRIANGLES);
            glTexCoord2f(0, 1);
            glVertex3f((maxX + 0.1) * i, (midY - 1.2) * j, lowZ);
            glTexCoord2f(1, 1);
            glVertex3f((maxX + 0.1) * i, midY * j, lowZ);
            glTexCoord2f(1, 0);
            glVertex3f(outX * i, midY * j, lowZ);
            glEnd();

            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(midX * i, midY * j, lowZ);
            glTexCoord2f(1, 0);
            glVertex3f(midX * i, medY * j, lowZ);
            glTexCoord2f(1, 1);
            glVertex3f(midX * i, medY * j, midZ);
            glTexCoord2f(0, 1);
            glVertex3f(midX * i, midY * j, midZ);
            glEnd();
        }
    }
    textures->unbind();
    //  Laterais
    //  Tras
    textures->bind(TEX_CARBACK);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, lowY, lowZ);
    glTexCoord2f(1, 1);
    glVertex3f(maxX, lowY, medZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, lowY, medZ);
    glTexCoord2f(0, 0);
    glVertex3f(-maxX, lowY, lowZ);
    glEnd();
    textures->unbind();

    //  Frente
    textures->bind(TEX_CARFRONT);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, maxY, lowZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, maxY, midZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, maxY, midZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, maxY, lowZ);
    glEnd();
    textures->unbind();
    // Direita e Esquerda
    if (mode == GL_FILL)
    {
        glColor3f(1, 0, 0);
        for (int i = -1; i <= 1; i += 2)
        {
            glBegin(GL_QUAD_STRIP);
            glVertex3f(maxX * i, medY, lowZ);
            glVertex3f(maxX * i, maxY, lowZ);
            for (float angulo = 0; angulo <= 180; angulo += 20)
            {
                float y = cos(angulo * M_PI / 180.0) * 6 + (medY + midY) / 2;
                float z = sin(angulo * M_PI / 180.0) * 6;

                if (angulo == 60)
                {
                    glVertex3f(maxX * i, y, z);
                    glVertex3f(maxX * i, maxY, midZ);
                }
                else if (angulo == 80)
                {
                    glVertex3f(maxX * i, y, z);
                    glVertex3f(maxX * i, medY, medZ);
                }
                else if (angulo == 100)
                {
                    glVertex3f(maxX * i, y, z);
                    glVertex3f(maxX * i, 0, medZ);
                }
                else if (angulo < 60)
                {
                    glVertex3f(maxX * i, y, z);
                    glVertex3f(maxX * i, maxY, z);
                }
                else
                {
                    glVertex3f(maxX * i, y, z);
                    glVertex3f(maxX * i, 0, z);
                }
            }
            glVertex3f(maxX * i, midY, lowZ);
            glVertex3f(maxX * i, 0, lowZ);
            glEnd();

            glBegin(GL_QUAD_STRIP);
            glVertex3f(maxX * i, -medY, lowZ);
            glVertex3f(maxX * i, lowY, lowZ);
            for (float angulo = 0; angulo <= 180; angulo += 20)
            {
                float y = cos(angulo * M_PI / 180.0) * 6 + (medY + midY) / 2;
                float z = sin(angulo * M_PI / 180.0) * 6;

                if (angulo == 80)
                {
                    glVertex3f(maxX * i, -y, z);
                    glVertex3f(maxX * i, lowY, medZ);
                }
                else if (angulo == 100)
                {
                    glVertex3f(maxX * i, -y, z);
                    glVertex3f(maxX * i, 0, medZ);
                }
                else if (angulo < 80)
                {
                    glVertex3f(maxX * i, -y, z);
                    glVertex3f(maxX * i, lowY, z);
                }
                else
                {
                    glVertex3f(maxX * i, -y, z);
                    glVertex3f(maxX * i, 0, z);
                }
            }
            glVertex3f(maxX * i, -midY, lowZ);
            glVertex3f(maxX * i, 0, lowZ);
            glEnd();
        }
        textures->bind(TEX_CARNUMBER);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f((maxX + 0.1), -midY, lowZ);
        glTexCoord2f(1, 0);
        glVertex3f((maxX + 0.1), midY, lowZ);
        glTexCoord2f(1, 1);
        glVertex3f((maxX + 0.1), midY, midZ);
        glTexCoord2f(0, 1);
        glVertex3f((maxX + 0.1), -midY, midZ);
        glEnd();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f((-maxX + 0.01), -midY, lowZ);
        glTexCoord2f(1, 0);
        glVertex3f((-maxX + 0.01), midY, lowZ);
        glTexCoord2f(1, 1);
        glVertex3f((-maxX + 0.01), midY, midZ);
        glTexCoord2f(0, 1);
        glVertex3f((-maxX + 0.01), -midY, midZ);
        glEnd();
        textures->unbind();
    }

    //   Meio
    // Traseira
    textures->bind(TEX_CARTOPBACK);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, lowY, medZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, -medY, medZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, -medY, medZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, lowY, medZ);
    glEnd();
    textures->unbind();

    textures->bind(TEX_CARWINDOW);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, -medY, medZ);
    glTexCoord2f(1, 0);
    glVertex3f(medX, -midY, maxZ);
    glTexCoord2f(1, 1);
    glVertex3f(-medX, -midY, maxZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, -medY, medZ);
    glEnd();
    textures->unbind();

    // Frente
    textures->bind(TEX_CARTOPFRONT);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, maxY, midZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, medY, medZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, medY, medZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, maxY, midZ);
    glEnd();
    textures->unbind();

    textures->bind(TEX_CARWINDOW);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(medX, midY, maxZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, medY, medZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, medY, medZ);
    glTexCoord2f(0, 1);
    glVertex3f(-medX, midY, maxZ);
    glEnd();
    textures->unbind();

    // Esquerda
    textures->bind(TEX_CARWINDOW);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-medX, -midY, maxZ);
    glTexCoord2f(1, 0);
    glVertex3f(-medX, midY, maxZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, medY, medZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, -medY, medZ);
    glEnd();
    textures->unbind();
    // Direita
    textures->bind(TEX_CARWINDOW);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(medX, -midY, maxZ);
    glTexCoord2f(1, 0);
    glVertex3f(medX, midY, maxZ);
    glTexCoord2f(1, 1);
    glVertex3f(maxX, medY, medZ);
    glTexCoord2f(0, 1);
    glVertex3f(maxX, -medY, medZ);
    glEnd();
    textures->unbind();

    // Teto
    textures->bind(TEX_CARTOP);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(medX, -midY, maxZ);
    glTexCoord2f(1, 0);
    glVertex3f(medX, midY, maxZ);
    glTexCoord2f(1, 1);
    glVertex3f(-medX, midY, maxZ);
    glTexCoord2f(0, 1);
    glVertex3f(-medX, -midY, maxZ);
    glEnd();
    textures->unbind();

    // Tail
    textures->bind(TEX_CARTAIL);
    for (int i = -1; i <= 1; i += 2)
    {
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(tMaxX * i, tMedY, medZ);
        glTexCoord2f(1, 0);
        glVertex3f(tMaxX * i, tMidY, tMinZ);
        glTexCoord2f(1, 1);
        glVertex3f(tMinX * i, tMidY, tMinZ);
        glTexCoord2f(0, 1);
        glVertex3f(tMinX * i, tMedY, medZ);
        glEnd();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(tMaxX * i, tMaxY, medZ);
        glTexCoord2f(1, 0);
        glVertex3f(tMaxX * i, tMedY, tMinZ);
        glTexCoord2f(1, 1);
        glVertex3f(tMinX * i, tMedY, tMinZ);
        glTexCoord2f(0, 1);
        glVertex3f(tMinX * i, tMaxY, medZ);
        glEnd();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(tMaxX * i, tMedY, medZ);
        glTexCoord2f(1, 0);
        glVertex3f(tMaxX * i, tMaxY, medZ);
        glTexCoord2f(1, 1);
        glVertex3f(tMaxX * i, tMedY, tMinZ);
        glTexCoord2f(0, 1);
        glVertex3f(tMaxX * i, tMidY, tMinZ);
        glEnd();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(tMinX * i, tMedY, medZ);
        glTexCoord2f(1, 0);
        glVertex3f(tMinX * i, tMaxY, medZ);
        glTexCoord2f(1, 1);
        glVertex3f(tMinX * i, tMedY, tMinZ);
        glTexCoord2f(0, 1);
        glVertex3f(tMinX * i, tMidY, tMinZ);
        glEnd();
    }

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, tMedY, tMaxZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, tMinY, tMaxZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, tMinY, tMaxZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, tMedY, tMaxZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, tMaxY, tMinZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, tLowY, tMinZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, tLowY, tMinZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, tMaxY, tMinZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(maxX, tMaxY, tMinZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, tMedY, tMaxZ);
    glTexCoord2f(1, 1);
    glVertex3f(maxX, tMinY, tMaxZ);
    glTexCoord2f(0, 1);
    glVertex3f(maxX, tLowY, tMinZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-maxX, tMaxY, tMinZ);
    glTexCoord2f(1, 0);
    glVertex3f(-maxX, tMedY, tMaxZ);
    glTexCoord2f(1, 1);
    glVertex3f(-maxX, tMinY, tMaxZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, tLowY, tMinZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-maxX, tLowY, tMinZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, tLowY, tMinZ);
    glTexCoord2f(1, 1);
    glVertex3f(maxX, tMinY, tMaxZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, tMinY, tMaxZ);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-maxX, tMaxY, tMinZ);
    glTexCoord2f(1, 0);
    glVertex3f(maxX, tMaxY, tMinZ);
    glTexCoord2f(1, 1);
    glVertex3f(maxX, tMedY, tMaxZ);
    glTexCoord2f(0, 1);
    glVertex3f(-maxX, tMedY, tMaxZ);
    glEnd();
    textures->unbind();
    glPopMatrix();
    glPopMatrix();
}

void Car::drawQuadStrip(float radius1, float radius2, float width1, float width2)
{
    textures->bind(TEX_WHEELCOLOR);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 12; i++)
    {
        float angle = i * 2 * M_PI / 12;
        glTexCoord2f(0, 0);
        glVertex3f(cos(angle) * radius1, sin(angle) * radius1, width1);
        glTexCoord2f(0, 1);
        glVertex3f(cos(angle) * radius2, sin(angle) * radius2, width2);
    }
    glTexCoord2f(0, 0);
    glVertex3f(cos(0) * radius1, sin(0) * radius1, width1);
    glTexCoord2f(0, 1);
    glVertex3f(cos(0) * radius2, sin(0) * radius2, width2);
    glEnd();
    textures->unbind();
}

void Car::drawWheel(float radius, float width)
{
    drawQuadStrip(radius, radius, -width, width);
    drawQuadStrip(radius, radius * 0.75, width, width);
    drawQuadStrip(radius, radius * 0.25, -width, -width);
    drawQuadStrip(radius * 0.25, radius * 0.25, -width, -width * 2);

    textures->bind(TEX_WHEEL);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 12; i++)
    {
        float angle = i * 2 * M_PI / 12;
        glTexCoord2f(cos(angle) * (radius / 12) + 0.5, sin(angle) * (radius / 12) + 0.5);
        glVertex3f(cos(angle) * (radius * 0.75), sin(angle) * (radius * 0.75), width);
    }
    glEnd();
    textures->unbind();
}

vec3 Car::getCarPos()
{
    return carPos;
}

void Car::setCarPos(vec3 carPos)
{
    this->carPos = carPos;
}

void Car::setCarPosX(float carPos)
{
    this->carPos.x = carPos;
}

void Car::setCarPosY(float carPos)
{
    this->carPos.y = carPos;
}

void Car::setCarPosZ(float carPos)
{
    this->carPos.z = carPos;
}

void Car::setCarRotZ(float rotZ)
{
    this->rotZ += rotZ;
}

void Car::setCarRotX(float rotX)
{
    this->rotX = rotX;
}

int Car::getDirection()
{
    return direction;
}

void Car::setDirection(int direction)
{
    this->direction = direction;
}

float Car::getSpeed()
{
    return speed;
}

void Car::colision(int type)
{
    if (type == 1)
    {
        this->speed = 0;
        this->direction = 0;
    }
    if (type == 2)
    {
        this->speed = speed / 1.2;
    }
}
