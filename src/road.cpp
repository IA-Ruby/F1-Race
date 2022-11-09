#include "../header/road.h"

#include <GL/gl.h>

Road::Road(GLubyte colorRoad[3], GLubyte colorBG[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->colorRoad[i] = colorRoad[i];
        this->colorBG[i] = colorBG[i];
    }

    for (int i = 0; i < 30; i++)
    {
        cordY.push_back(i * 500.f);
    }
}

void Road::draw(float speed)
{
    //  Atuaiza as variaveis com base na velocidade informada
    updRoad(speed);

    // Desenha a pista
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
    for (int i = 0; i < cordY.size(); i++)
    {
        glPushMatrix();
            glTranslatef(0, cordY[i], -5);
            glColor3ubv(colorRoad);
            drawQuad(3.f, 100.f);
        glPopMatrix();
    }

    // Desenha os inimigos
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].draw();
    }
}

void Road::updRoad(float speed)
{
    // Verifica se é necessario adicionar um novo carro

    if (enemies.empty())
    { // Caso não exista nenhum carro na fila
        if(speed <= 150)
        {    
            enemies.push_front(Car( colorBG, glm::vec3((rand() % 120 - 60), -4000, 0), 150.f));
        }
        else
        {
            enemies.push_back(Car(colorBG, glm::vec3(rand() % 120 - 60, 24000, 0), 150.f));
        }
    }
    else if (rand() % 100 == 1)
    { // Joga um d100 pra ver se um novo carro é adicionado, pra ficar mais dinamico

        // Verifica a velocidade do jogador é menor que a velocidade media dos outros carros,
        // && se o inimigo mais proximo não está na frente da linha de surgimento
        if (speed <= 150 && enemies.front().getCarPos().y > -500)
        {
            enemies.push_front(Car(colorBG, glm::vec3((rand() % 120 - 60), -4000, 0), 150.f));
            enemies.front().setTexId(carTexId);
        }
        // Verifica se o inimigo mais longe está antes da linha de surgimento
        else if (enemies.back().getCarPos().y <= 20000.f)
        {
            enemies.push_back(Car(colorBG, glm::vec3(rand() % 120 - 60, 24000, 0), 150.f));
            enemies.back().setTexId(carTexId);
        }
    }

    // Atualiza a posição dos carros após a tentativa de adição de um novo veiculo
    for (int i = 0; i < enemies.size(); i++)
    {
        // Muda a posição do carro para que com cabe na sua velocidade - a velocidade do jogador
        enemies[i].setCarPos(enemies[i].getCarPos().y + enemies[i].getSpeed() - speed);

        if (enemies[i].getCarPos().y > 14000)
        {
            enemies[i].setCarPos( glm::vec3(enemies[i].getCarPos().x,
                                            enemies[i].getCarPos().y,
                                            -(enemies[i].getCarPos().y-14000)/100));
        }

        // Verifica se o carro deve ser deletado com base na sua posição
        if (enemies.front().getCarPos().y < -4000)
        { // Carros muito pra trás são deletados
            enemies.pop_front();
            i--;
        }
        
        if (enemies.back().getCarPos().y > 36000)
        { // Carros muito a frente também são deletados
            enemies.pop_back();
            i--;
        }
    }

    // Atualiza as linhas
    for (int i = 0; i < cordY.size(); i++)
    {
        cordY[i] -= speed;
        if (cordY[i] < -200.f)
        {
            cordY.push_back(cordY[i] + (cordY.size() * 500.f));
            cordY.pop_front();
            i--;
        }
    } 
}

void Road::drawQuad(float x, float y)
{
    glBegin(GL_QUADS);
        glVertex3f(x, -y, 0);
        glVertex3f(x, y, 0);
        glVertex3f(-x, y, 0);
        glVertex3f(-x, -y, 0);
    glEnd();
}

void Road::setCarTexId(unsigned int carTexId)
{
    this->carTexId = carTexId;
}