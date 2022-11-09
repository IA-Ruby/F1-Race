#include "../header/tree.h"
#include <GL/gl.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

Tree::Tree(GLubyte colorTree[3], vec3 cordTree)
{
    for (int i = 0; i < 3; i++)
    {
        this->colorTree[i] = colorTree[i];
    }
    int aux = rand() % 4 + 8;
    for (int i = 0; i < aux; i++)
    {
        angleLeavesX.push_back((360 / aux) * i);
        angleLeavesZ.push_back(rand() % 45 - 15);
    }
    this->sizeTree = rand() % 10 + 8;
    this->widthTree = this->sizeTree / 2;
    this->cordTree = cordTree;
}

void Tree::draw()
{
    glColor3ubv(colorTree);
    for (int i = 0; i < sizeTree; i++)
    {
        float aux = widthTree - (widthTree / sizeTree * i) + 1;
        glPushMatrix();
        glRotatef(90, 0, 0, 1);
        glRotatef(i, 1, 0, 0);
        glTranslatef(0, 0, i * 10);
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j < 12; j++)
        {
            float angulo = j * 2 * M_PI / 12;
            glVertex3f(cos(angulo) * (aux), sin(angulo) * (aux), 0);
            glVertex3f(cos(angulo) * (aux), sin(angulo) * (aux), 10);
        }
        glVertex3f(cos(0) * (aux), sin(0) * (aux), 0);
        glVertex3f(cos(0) * (aux), sin(0) * (aux), 10);
        glEnd();
        glPopMatrix();
    }

    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glRotatef(sizeTree, 1, 0, 0);
    glTranslatef(0, 0, ((sizeTree - 1) * 10));
    for (int i = 0; i < angleLeavesZ.size(); i++)
    {
        glPushMatrix();
        glRotatef(angleLeavesX[i], 0, 0, 1);
        glRotatef(angleLeavesZ[i], 1, 0, 0);
        glScalef((sizeTree + widthTree) / 2, (sizeTree + widthTree) / 2, (sizeTree + widthTree) / 2);
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 0, 1);
            glVertex3f(0, 1, 1.3);
            glVertex3f(1, 2, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 0, 1);
            glVertex3f(0, 1, 1.3);
            glVertex3f(-1, 2, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0, 1, 1.3);
            glVertex3f(0, 2, 1.7);
            glVertex3f(1, 3, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 1, 1.3);
            glVertex3f(0, 2, 1.7);
            glVertex3f(-1, 3, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0, 2, 1.7);
            glVertex3f(0, 3, 2.0);
            glVertex3f(1, 4, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 2, 1.7);
            glVertex3f(0, 3, 2.0);
            glVertex3f(-1, 4, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0, 3, 2.0);
            glVertex3f(0, 4, 2.1);
            glVertex3f(1, 5, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 3, 2.0);
            glVertex3f(0, 4, 2.1);
            glVertex3f(-1, 5, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0, 4, 2.1);
            glVertex3f(0, 5, 2.0);
            glVertex3f(1, 6, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 4, 2.1);
            glVertex3f(0, 5, 2.0);
            glVertex3f(-1, 6, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0, 5, 2.0);
            glVertex3f(0, 6, 1.7);
            glVertex3f(1, 7, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 5, 2.0);
            glVertex3f(0, 6, 1.7);
            glVertex3f(-1, 7, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0, 6, 1.7);
            glVertex3f(0, 7, 1.3);
            glVertex3f(1, 8, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 6, 1.7);
            glVertex3f(0, 7, 1.3);
            glVertex3f(-1, 8, 0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(0, 7, 1.3);
            glVertex3f(0, 9, 0);
        glEnd();

        glPopMatrix();
    }
    glPopMatrix();
}

void Tree::setCordTree(vec3 cordTree)
{
    this->cordTree = cordTree;
}

void Tree::setCordYTree(float cordTree)
{
    this->cordTree.y = cordTree;
}

void Tree::setCordZTree(float cordTree)
{
    this->cordTree.z = cordTree;
}

vec3 Tree::getCordTree()
{
    return cordTree;
}