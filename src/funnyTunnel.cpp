#include "../header/funnyTunnel.h"
#include <GL/gl.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

FunnyTunnel::FunnyTunnel(GLubyte colorTunnel[3], GLubyte colorBG[3]){
    for(int i=0; i<3; i++){
        this->colorTunnel[i] = colorTunnel[i];
        this->colorBG[i] - colorBG[i];
    }
    for(int i=-2; i<80; i++){
        cordY.push_back(i*1000);
    }
}

void FunnyTunnel::draw(float speed, int dist){
    auxRot += dist/5*(speed/90);
    if(auxRot<0)
        auxRot = 360+auxRot;
    else if(auxRot>360)
        auxRot = auxRot-360;
        
    updTunnel(speed);
    glLineWidth(1.0f);
    drawMode(GL_FILL,colorBG, 100.f);
    glLineWidth(2.0f);
    drawMode(GL_LINE,colorTunnel, 99.8f);
}

void FunnyTunnel::drawMode(int mode, GLubyte color[3], float scale){
    // Obstaculo

    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glPushMatrix();
        glTranslatef(0,0,90);
        glRotatef(auxRot, 0, 1, 0);
        for(int i=0; i<cordY.size()-1; i++){
            glPushMatrix();
                glScalef(scale,1,scale);
                glColor3ubv(color);
                glBegin(GL_QUAD_STRIP);    
                    for (float angulo = 0; angulo <= 360; angulo += 30){
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

void FunnyTunnel::updTunnel(float speed){
    for(int i=0; i<cordY.size(); i++){
        cordY[i] -= speed;
        if(cordY[i] <= -2000){
            cordY.pop_front();
            cordY.push_back(cordY.back()+1000);
            i--;
        }
    }
}