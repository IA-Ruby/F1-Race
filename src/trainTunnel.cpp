#include "../header/trainTunnel.h"
#include <GL/gl.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

TrainTunnel::TrainTunnel(GLubyte colorRoad[3], GLubyte colorWall[3], GLubyte colorBG[3]){
    for(int i=0; i<3; i++){
        this->colorRoad[i] = colorRoad[i];
        this->colorWall[i] = colorWall[i];
        this->colorBG[i] = colorBG[i];
    }
    for(int i=-2; i<40; i++){
        cordY.push_back(i*400);
    }
}

void TrainTunnel::draw(float speed){
    updTunnel(speed);
    drawMode(GL_LINE, colorRoad, colorWall);
    drawMode(GL_FILL, colorBG, colorBG);
}

void TrainTunnel::drawMode(int mode, GLubyte color1[3], GLubyte color2[3]){
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    //desenha kapa
    glPushMatrix();
        glTranslatef(0,0,-5.1);
        for(int i=0; i<cordY.size()-1; i++){
            glColor3ubv(color1);
            glBegin(GL_QUADS);  glVertex3f( -80,   cordY[i], 0);
                                glVertex3f(  80,   cordY[i], 0);
                                glVertex3f(  80, cordY[i+1], 0);
                                glVertex3f( -80, cordY[i+1], 0); glEnd();
            glPushMatrix();
                glScalef(80,1,80);
                glColor3ubv(color2);
                glBegin(GL_QUAD_STRIP);    
                    for (float angulo = 0; angulo <= 180; angulo += 20){
                        float x = cos(angulo*M_PI/180.0);
                        float z = sin(angulo*M_PI/180.0);
                        glVertex3f(x,cordY[i],z);
                        glVertex3f(x,cordY[i+1],z);
                    }
                glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void TrainTunnel::updTunnel(float speed){
    for(int i=0; i<cordY.size(); i++){
        cordY[i] -= speed;
        if(cordY[i] <= -800){
            cordY.pop_front();
            cordY.push_back(cordY.back()+400);
            i--;
        }
    }
}